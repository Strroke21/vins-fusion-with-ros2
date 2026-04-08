#!/usr/bin/env python3

import math
import threading
from collections import deque
from typing import Optional

import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

from nav_msgs.msg import Odometry
from sensor_msgs.msg import Imu
from pymavlink import mavutil


class VinsToFCBridge(Node):
    def __init__(self):
        super().__init__('vins_to_fc_bridge')

        # ROS
        self.ODOM_TOPIC = '/odometry'
        self.IMU_TOPIC = '/camera/camera/imu'
        self.QOS_BEST_EFFORT = True
        self.camera_orientation = 0 # 0: 45 deg, 1: downward, 2: forward
        self.converted_odom_pub = self.create_publisher(Odometry, '/converted_odom', 10)

        # MAVLink conection
        self.MAVLINK_URL = '/dev/ttyACM0' #'tcp:127.0.0.1:5762'
        self.SOURCE_SYSTEM = 191
        self.SOURCE_COMPONENT = int(mavutil.mavlink.MAV_COMP_ID_VISUAL_INERTIAL_ODOMETRY)

        # Initial Yaw
        self.YAW_INIT_SECONDS = 3.0

        # Send rate
        self.SEND_RATE_HZ = 30.0

        # Estimator metadata
        self.QUALITY = 100
        self.ESTIMATOR_TYPE = 3  # MAV_ESTIMATOR_TYPE_VIO

        # Time handling
        self.USE_FC_BOOT_TIME = True
        self.boot_0 = None
        self.t_bag_start = None

        self.script_mode = 0 #0 for IMU+VO, 1 for VO only

        """
        Frame notation:
        R_A_B means: vector in frame A = R_A_B @ vector in frame B

        Frames:
        W : VINS world frame
        C : VINS camera frame from /odometry
        B : Aircraft body frame
        N : FC Local NED frame
        N': Intermediate NED-like frame after fixed axis conversion only
        """

        # Camera-to-body mount for 45 degree mount
        if self.camera_orientation == 0:
            self.R_C_B = np.array([
                [0.0, 1.0, 0.0],
                [-0.707, 0.0, 0.707],
                [0.707, 0.0, 0.707]
            ], dtype=float)

        #camera-to-body mount for 90 degree downward facing
        elif self.camera_orientation == 1:
            self.R_C_B = np.array([
                [0.0, 1.0, 0.0],
                [-1.0, 0.0, 0.0],
                [0.0, 0.0, 1.0]
            ], dtype=float)

        #camera-to-body mount forward facing 
        elif self.camera_orientation == 2:
            self.R_C_B = np.array([
                [0.0, 1.0, 0.0],
                [0.0, 0.0, 1.0],
                [1.0, 0.0, 0.0]
            ], dtype=float) 

        self.R_B_C = self.R_C_B.T

        # Fixed convention conversion: W -> N' (swap XY, flip Z)
        self.R_conv = np.array([
            [0.0, 1.0, 0.0],
            [1.0, 0.0, 0.0],
            [0.0, 0.0, -1.0]
        ], dtype=float)

        # Final mapping: W -> N = R_psi @ R_conv, solved after yaw init
        self.R_psi = None
        self.R_N_W = None
        self.p_W_0 = None
        self.ready = False

        self.lock = threading.Lock()

        self.latest_odom: Optional[Odometry] = None
        self.fc_boot_minus_unix_us: Optional[int] = None
        self.latest_fc_yaw_rad: Optional[float] = None

        self.wx = 0.0
        self.wy = 0.0
        self.wz = 0.0

        self.init_started = False
        self.init_start_ros_sec = None

        self.fc_yaw_samples = deque()
        self.vins_yaw_samples = deque()

        self.yaw_fc0 = None
        self.yaw_vins0 = None

        self.reset_counter = 0

        self.get_logger().info(f'Connecting MAVLink: {self.MAVLINK_URL}')
        self.mav = mavutil.mavlink_connection(
            self.MAVLINK_URL,
            baud=115200,
            source_system=self.SOURCE_SYSTEM,
            source_component=self.SOURCE_COMPONENT,
        )

        self.get_logger().info('Waiting for MAVLink heartbeat...')
        self.mav.wait_heartbeat(timeout=10)
        self.get_logger().info(
            f'Heartbeat received from sys={self.mav.target_system}, comp={self.mav.target_component}'
        )

        self.mav.mav.request_data_stream_send(
            self.mav.target_system,
            self.mav.target_component,
            mavutil.mavlink.MAV_DATA_STREAM_ALL,
            30,
            1,
        )

        self.mav_rx_thread = threading.Thread(target=self.mav_rx_loop, daemon=True)
        self.mav_rx_thread.start()

        qos = QoSProfile(
            history=HistoryPolicy.KEEP_LAST,
            depth=200,
            reliability=ReliabilityPolicy.BEST_EFFORT if self.QOS_BEST_EFFORT else ReliabilityPolicy.RELIABLE,
        )

        self.sub = self.create_subscription(Odometry, self.ODOM_TOPIC, self.odom_cb, qos)
        self.imu_sub = self.create_subscription(Imu,'/camera/camera/imu',self.imu_cb,qos)
        self.timer = self.create_timer(1.0 / self.SEND_RATE_HZ, self.send_odometry)

        self.get_logger().info('VINS -> FC bridge started')

    def mav_rx_loop(self):
        while rclpy.ok():
            try:
                msg = self.mav.recv_match(blocking=True, timeout=0.2)
                if msg is None:
                    continue

                mtype = msg.get_type()
                if mtype == 'VFR_HUD':
                    yaw_deg = float(msg.heading)
                    yaw_rad = self.wrap_pi(math.radians(yaw_deg))
                    with self.lock:
                        self.latest_fc_yaw_rad = yaw_rad

                elif mtype == 'SYSTEM_TIME':
                    if self.boot_0 is None:
                        self.boot_0 = getattr(msg, 'time_boot_ms', 0)

                    if getattr(msg, 'time_unix_usec', 0) > 0 and getattr(msg, 'time_boot_ms', 0) > 0:
                        candidate = int(msg.time_boot_ms) * 1000 - int(msg.time_unix_usec)
                        with self.lock:
                            if self.fc_boot_minus_unix_us is None:
                                self.fc_boot_minus_unix_us = candidate
                            else:
                                alpha = 0.5
                                self.fc_boot_minus_unix_us = int(
                                    (1.0 - alpha) * self.fc_boot_minus_unix_us + alpha * candidate
                                )

            except Exception as e:
                self.get_logger().warn(f'MAVLink RX warning: {e}')

    def imu_cb(self, msg):
        self.wx = msg.angular_velocity.x
        self.wy = msg.angular_velocity.y
        self.wz = msg.angular_velocity.z

    def odom_cb(self, msg: Odometry):
        with self.lock:
            self.latest_odom = msg

        t_ros = self.ros_stamp_to_sec(msg.header.stamp)

        if not self.init_started:
            self.init_started = True
            self.init_start_ros_sec = t_ros
            #self.get_logger().info('Started initial yaw collection window')

        p_W = np.array([
            msg.pose.pose.position.x,
            msg.pose.pose.position.y,
            msg.pose.pose.position.z,
        ], dtype=float)

        q_W_C = self.quat_ros_to_wxyz(msg.pose.pose.orientation)
        #self.get_logger().info(f'q_W_C = {q_W_C}')
        R_W_C = self.quat_to_rotmat(q_W_C)
        R_W_B = R_W_C @ self.R_C_B

        with self.lock:
            fc_yaw = self.latest_fc_yaw_rad

        if not self.ready:
            # During init, only use the known fixed axis conversion.
            R_Nprime_B = self.R_conv @ R_W_B
            yaw_vins_body = self.yaw_from_rotmat(R_Nprime_B)

            roll_vins, pitch_vins, yaw_vins = self.rpy_from_rotmat(R_Nprime_B)
            # self.get_logger().info(
            #     f'VINS init RPY [deg] | roll={math.degrees(roll_vins):.2f}, '
            #     f'pitch={math.degrees(pitch_vins):.2f}, '
            #     f'yaw={math.degrees(yaw_vins):.2f}'
            # )

            if fc_yaw is not None:
                self.fc_yaw_samples.append(fc_yaw)
                self.vins_yaw_samples.append(yaw_vins_body)

            if (t_ros - self.init_start_ros_sec) >= self.YAW_INIT_SECONDS:
                self.finish_initial_alignment(p_W)
            return

        # Optional runtime debug after alignment
        R_N_B = self.R_N_W @ R_W_B
        roll_vins, pitch_vins, yaw_vins = self.rpy_from_rotmat(R_N_B)
        # self.get_logger().info(
        #     f'VINS RPY [deg] | roll={math.degrees(roll_vins):.2f}, '
        #     f'pitch={math.degrees(pitch_vins):.2f}, '
        #     f'yaw={math.degrees(yaw_vins):.2f}'
        # )

    def finish_initial_alignment(self, p_W_0_now):
        if len(self.fc_yaw_samples) == 0 or len(self.vins_yaw_samples) == 0:
            self.get_logger().warn('Initial alignment ended but yaw samples were insufficient')
            return

        self.yaw_fc0 = self.circular_mean(self.fc_yaw_samples)
        self.yaw_vins0 = self.circular_mean(self.vins_yaw_samples)
        delta_yaw = self.wrap_pi(self.yaw_fc0 - self.yaw_vins0)

        cy = math.cos(delta_yaw)
        sy = math.sin(delta_yaw)

        self.R_psi = np.array([
            [cy, -sy, 0.0],
            [sy,  cy, 0.0],
            [0.0, 0.0, 1.0],
        ], dtype=float)

        # Final mapping: W -> N
        self.R_N_W = self.R_psi @ self.R_conv
        self.p_W_0 = np.array(p_W_0_now, dtype=float)
        self.ready = True

        self.get_logger().info(
            f'Alignment ready | yaw_fc0={math.degrees(self.yaw_fc0):.2f} deg, '
            f'yaw_vins0={math.degrees(self.yaw_vins0):.2f} deg, '
            f'delta={math.degrees(delta_yaw):.2f} deg'
        )
        #self.get_logger().info(f'R_N_W =\n{self.R_N_W}')
        #self.get_logger().info(f'p_W_0 = {self.p_W_0}')


    def send_odometry(self):
        with self.lock:
            msg = self.latest_odom
            fc_boot_minus_unix_us = self.fc_boot_minus_unix_us

        if msg is None or not self.ready:
            return

        try:
            odom = self.convert_odom(msg, fc_boot_minus_unix_us)
            self.publish_converted_odom(msg, odom)

            # --- Extract RPY from quaternion ---
            q = odom['q']
            R = self.quat_to_rotmat(q)
            roll, pitch, yaw = self.rpy_from_rotmat(R)

            # --- Build pose covariance (21 → 36 not needed, just reuse upper diag) ---
            cov_pose = np.array(odom['pose_covariance'])
            
            # --- Send VISION_POSITION_ESTIMATE ---
            self.mav.mav.vision_position_estimate_send(
                odom['time_usec'],
                odom['x'],
                odom['y'],
                odom['z'],
                roll,
                pitch,
                yaw,
                cov_pose
            )

            # --- Build velocity covariance (3x3 flattened) ---
            vel_cov_full = np.array(odom['velocity_covariance'])
            vel_cov = np.array([
                vel_cov_full[0], 0, 0,
                0, vel_cov_full[6], 0,
                0, 0, vel_cov_full[11]
            ])

            # --- Send VISION_SPEED_ESTIMATE ---
            self.mav.mav.vision_speed_estimate_send(
                odom['time_usec'],
                odom['vx'],
                odom['vy'],
                odom['vz'],
                vel_cov
            )

            msg = self.mav.recv_match("STATUSTEXT", blocking=True)

            self.get_logger().info(f"time_usec:{odom['time_usec']},x: {odom['x']},y: {odom['y']},z: {odom['z']},q: {roll, pitch,yaw},vx: {odom['vx']},vy: {odom['vy']}, vz: {odom['vz']}")
            self.get_logger().info(f"[messages: {msg}")
        except Exception as e:
            self.get_logger().warn(f'Failed to send vision estimate: {e}')

    '''def send_odometry(self):
        with self.lock:
            msg = self.latest_odom
            fc_boot_minus_unix_us = self.fc_boot_minus_unix_us

        if msg is None or not self.ready:
            return

        try:
            odom = self.convert_odom(msg, fc_boot_minus_unix_us)
            self.publish_converted_odom(msg, odom)
            # self.mav.mav.odometry_send(
            #     odom['time_usec'],
            #     odom['frame_id'],
            #     odom['child_frame_id'],
            #     odom['x'],
            #     odom['y'],
            #     odom['z'],
            #     odom['q'],
            #     odom['vx'],
            #     odom['vy'],
            #     odom['vz'],
            #     odom['rollspeed'],
            #     odom['pitchspeed'],
            #     odom['yawspeed'],
            #     odom['pose_covariance'],
            #     odom['velocity_covariance'],
            #     odom['reset_counter'],
            #     odom['estimator_type'],
            #     odom['quality'],
            # )

        except Exception as e:
            self.get_logger().warn(f'Failed to send odometry: {e}')'''

    def ros_cov36_to_mav_upper21_with_default(self,cov36, default_diag):
        """
        Convert ROS 6x6 covariance (36 elems, row-major) to MAVLink upper-triangular 21 elems.
        If ROS covariance is missing / all zero / non-finite, use default diagonal values.

        State order assumed:
        [x, y, z, roll, pitch, yaw]
        """

        # default_diag must be length 6
        # example: [0.25, 0.25, 0.25, 0.04, 0.04, 0.04]

        use_default = False

        if cov36 is None or len(cov36) != 36:
            use_default = True
        else:
            # Check whether all entries are zero or invalid
            finite_vals = [v for v in cov36 if isinstance(v, (int, float)) and math.isfinite(v)]
            if len(finite_vals) != 36:
                use_default = True
            elif all(abs(v) < 1e-12 for v in cov36):
                use_default = True

        if use_default:
            C = [[0.0]*6 for _ in range(6)]
            for i in range(6):
                C[i][i] = float(default_diag[i])
        else:
            # reshape 36 -> 6x6
            C = [list(map(float, cov36[i*6:(i+1)*6])) for i in range(6)]

            # Optional safety: if diagonal is zero/non-finite, replace only that diagonal
            for i in range(6):
                if (not math.isfinite(C[i][i])) or abs(C[i][i]) < 1e-12:
                    C[i][i] = float(default_diag[i])

        # Convert to MAVLink upper triangular 21 elements
        out = []
        for i in range(6):
            for j in range(i, 6):
                out.append(float(C[i][j]))
        return out

    def convert_odom(self, msg: Odometry, fc_boot_minus_unix_us: Optional[int]):
        if self.t_bag_start is None:
            self.t_bag_start = self.ros_stamp_to_usec(msg.header.stamp)

        ros_unix_us = self.ros_stamp_to_usec(msg.header.stamp)

        if self.boot_0 is None:
            time_usec = ros_unix_us
        else:
            time_usec = self.boot_0 * 1000 + (ros_unix_us - self.t_bag_start)

        p_W = np.array([
            msg.pose.pose.position.x,
            msg.pose.pose.position.y,
            msg.pose.pose.position.z,
        ], dtype=float)

        v_W = np.array([
            msg.twist.twist.linear.x,
            msg.twist.twist.linear.y,
            msg.twist.twist.linear.z,
        ], dtype=float)

        w_W = np.array([
                self.wx,
                self.wy,
                self.wz
        ], dtype=float)

        q_W_C = self.quat_ros_to_wxyz(msg.pose.pose.orientation)
        R_W_C = self.quat_to_rotmat(q_W_C)
        R_W_B = R_W_C @ self.R_C_B
        R_N_B = self.R_N_W @ R_W_B

        q_N = self.rotmat_to_quat(R_N_B)
        p_N = self.R_N_W @ (p_W - self.p_W_0)
        v_N = self.R_N_W @ v_W
        w_B = self.R_B_C @ w_W

        #self.get_logger().info(f'p_N: {p_N}')
        #self.get_logger().info(f'v_N: {v_N}')
        #self.get_logger().info(f'q_N: {q_N}')
        #self.get_logger().info(f'w_N: {w_B}')

        frame_id = mavutil.mavlink.MAV_FRAME_LOCAL_NED
        child_frame_id = mavutil.mavlink.MAV_FRAME_BODY_FRD

        # pose_covariance = self.ros_cov36_to_mav_upper21(msg.pose.covariance)
        # velocity_covariance = self.ros_cov36_to_mav_upper21(msg.twist.covariance)
        # quality = max(-1, min(100, self.QUALITY))


        pose_covariance = self.ros_cov36_to_mav_upper21_with_default(msg.pose.covariance,
                                                                default_diag=[0.25, 0.25, 0.25, 0.04, 0.04, 0.04]
                                                                )

        velocity_covariance = self.ros_cov36_to_mav_upper21_with_default(msg.twist.covariance,
                                                                    default_diag=[0.09, 0.09, 0.09, 0.04, 0.04, 0.04]
                                                                    )

        quality = max(-1, min(100, self.QUALITY))

        #self.get_logger().info(f'time_usec: {time_usec},frame_id: {frame_id},child_frame_id: {child_frame_id},x: {float(p_N[0])},y: {float(p_N[1])},z: {float(p_N[2])},q: {[float(q_N[0]), float(q_N[1]), float(q_N[2]), float(q_N[3])]},vx: {float(v_N[0])},vy: {float(v_N[1])}, vz: {float(v_N[2])},rollspeed: {float(w_B[0])},pitchspeed: {float(w_B[1])},yawspeed: {float(w_B[2])},pose_covariance: {pose_covariance},velocity_covariance: {velocity_covariance},reset_counter: {int(self.reset_counter)},estimator_type: {int(self.ESTIMATOR_TYPE)},quality: {int(quality)}')

        return {
            'time_usec': time_usec,
            'frame_id': frame_id,
            'child_frame_id': child_frame_id,
            'x': float(p_N[0]),
            'y': float(p_N[1]),
            'z': float(p_N[2]),
            'q': [float(q_N[0]), float(q_N[1]), float(q_N[2]), float(q_N[3])],
            'vx': float(v_N[0]),
            'vy': float(v_N[1]),
            'vz': float(v_N[2]),
            'rollspeed': float(w_B[0]),
            'pitchspeed': float(w_B[1]),
            'yawspeed': float(w_B[2]),
            'pose_covariance': pose_covariance,
            'velocity_covariance': velocity_covariance,
            'reset_counter': int(self.reset_counter),
            'estimator_type': int(self.ESTIMATOR_TYPE),
            'quality': int(quality),
        }

    @staticmethod
    def wrap_pi(a: float) -> float:
        while a > math.pi:
            a -= 2.0 * math.pi
        while a < -math.pi:
            a += 2.0 * math.pi
        return a

    @staticmethod
    def quat_ros_to_wxyz(q_msg):
        return np.array([q_msg.w, q_msg.x, q_msg.y, q_msg.z], dtype=float)

    @staticmethod
    def quat_normalize(q):
        n = np.linalg.norm(q)
        if n < 1e-12:
            return np.array([1.0, 0.0, 0.0, 0.0], dtype=float)
        return q / n

    @classmethod
    def quat_to_rotmat(cls, q_wxyz):
        q = cls.quat_normalize(np.array(q_wxyz, dtype=float))
        w, x, y, z = q

        return np.array([
            [1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y - z * w),       2.0 * (x * z + y * w)],
            [2.0 * (x * y + z * w),       1.0 - 2.0 * (x * x + z * z), 2.0 * (y * z - x * w)],
            [2.0 * (x * z - y * w),       2.0 * (y * z + x * w),       1.0 - 2.0 * (x * x + y * y)],
        ], dtype=float)

    @classmethod
    def rotmat_to_quat(cls, R):
        R = np.array(R, dtype=float)
        tr = np.trace(R)

        if tr > 0.0:
            S = math.sqrt(tr + 1.0) * 2.0
            w = 0.25 * S
            x = (R[2, 1] - R[1, 2]) / S
            y = (R[0, 2] - R[2, 0]) / S
            z = (R[1, 0] - R[0, 1]) / S
        elif R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
            S = math.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2]) * 2.0
            w = (R[2, 1] - R[1, 2]) / S
            x = 0.25 * S
            y = (R[0, 1] + R[1, 0]) / S
            z = (R[0, 2] + R[2, 0]) / S
        elif R[1, 1] > R[2, 2]:
            S = math.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2]) * 2.0
            w = (R[0, 2] - R[2, 0]) / S
            x = (R[0, 1] + R[1, 0]) / S
            y = 0.25 * S
            z = (R[1, 2] + R[2, 1]) / S
        else:
            S = math.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1]) * 2.0
            w = (R[1, 0] - R[0, 1]) / S
            x = (R[0, 2] + R[2, 0]) / S
            y = (R[1, 2] + R[2, 1]) / S
            z = 0.25 * S

        return cls.quat_normalize(np.array([w, x, y, z], dtype=float))

    @staticmethod
    def yaw_from_rotmat(R):
        return math.atan2(R[1, 0], R[0, 0])

    @staticmethod
    def rpy_from_rotmat(R):
        roll = math.atan2(R[2, 1], R[2, 2])
        pitch = math.atan2(-R[2, 0], math.sqrt(R[2, 1] ** 2 + R[2, 2] ** 2))
        yaw = math.atan2(R[1, 0], R[0, 0])
        return roll, pitch, yaw

    @staticmethod
    def circular_mean(angles):
        if len(angles) == 0:
            return 0.0
        s = sum(math.sin(a) for a in angles)
        c = sum(math.cos(a) for a in angles)
        return math.atan2(s, c)

    @staticmethod
    def ros_cov36_to_mav_upper21(cov36):
        if cov36 is None or len(cov36) != 36:
            return [float('nan')] + [0.0] * 20

        C = np.array(cov36, dtype=float).reshape(6, 6)
        out = []
        for i in range(6):
            for j in range(i, 6):
                out.append(float(C[i, j]))
        return out

    @staticmethod
    def ros_stamp_to_sec(stamp):
        return float(stamp.sec) + float(stamp.nanosec) * 1e-9

    @staticmethod
    def ros_stamp_to_usec(stamp):
        return int(stamp.sec) * 1_000_000 + int(stamp.nanosec) // 1000

    @staticmethod
    def mav_upper21_to_ros_cov36(cov21):
        if cov21 is None or len(cov21) != 21:
            return [0.0] * 36

        C = np.zeros((6, 6), dtype=float)
        k = 0
        for i in range(6):
            for j in range(i, 6):
                C[i, j] = float(cov21[k])
                C[j, i] = float(cov21[k])
                k += 1

        return C.reshape(36).tolist()



    def publish_converted_odom(self, src_msg: Odometry, odom_dict):
        msg_out = Odometry()

        # Header
        msg_out.header = src_msg.header
        msg_out.header.frame_id = 'local_ned'
        msg_out.child_frame_id = 'body_frd'

        # Position
        msg_out.pose.pose.position.x = odom_dict['x']
        msg_out.pose.pose.position.y = odom_dict['y']
        msg_out.pose.pose.position.z = odom_dict['z']

        # Orientation
        # rotmat_to_quat() returns [w, x, y, z]
        q_wxyz = odom_dict['q']
        msg_out.pose.pose.orientation.w = q_wxyz[0]
        msg_out.pose.pose.orientation.x = q_wxyz[1]
        msg_out.pose.pose.orientation.y = q_wxyz[2]
        msg_out.pose.pose.orientation.z = q_wxyz[3]

        # Linear velocity
        msg_out.twist.twist.linear.x = odom_dict['vx']
        msg_out.twist.twist.linear.y = odom_dict['vy']
        msg_out.twist.twist.linear.z = odom_dict['vz']

        # Angular velocity
        msg_out.twist.twist.angular.x = odom_dict['rollspeed']
        msg_out.twist.twist.angular.y = odom_dict['pitchspeed']
        msg_out.twist.twist.angular.z = odom_dict['yawspeed']

        # Covariances
        msg_out.pose.covariance = self.mav_upper21_to_ros_cov36(odom_dict['pose_covariance'])
        msg_out.twist.covariance = self.mav_upper21_to_ros_cov36(odom_dict['velocity_covariance'])

        self.converted_odom_pub.publish(msg_out)




def main(args=None):
    rclpy.init(args=args)
    node = VinsToFCBridge()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()