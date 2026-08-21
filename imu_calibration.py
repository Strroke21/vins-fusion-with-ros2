#!/usr/bin/env python3
"""
Compute IMU noise params (acc_n, gyr_n, acc_w, gyr_w) from a ROS2 topic over a
known-in-flight interval of a rosbag.

Method (flight interval only):
- dt = median timestamp difference
- acc_n/gyr_n (noise density):  sigma_meas = std(diff(x))/sqrt(2);  n = sigma_meas * sqrt(dt)
- acc_w/gyr_w (bias random-walk density proxy): window means over T=1s, then
  w = std(diff(mean_windows)) / sqrt(T)

Assumptions:
- gyro in rad/s, accel in m/s^2 (SI)
- /camera/camera/imu publishes sensor_msgs/Imu with header.stamp filled
- You know flight interval relative to bag start (here: 120s..240s)

Run (bag):
  # Terminal 1
  ros2 bag play <bag_path> --clock

  # Terminal 2
  python3 imu_calibration.py --topic /camera/camera/imu --t0 120 --t1 240
"""

import argparse
import math
import sys
from dataclasses import dataclass
from typing import List, Tuple

import numpy as np
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from rclpy.qos import qos_profile_sensor_data



@dataclass
class Params:
    acc_n_xyz: np.ndarray
    gyr_n_xyz: np.ndarray
    acc_w_xyz: np.ndarray
    gyr_w_xyz: np.ndarray
    dt: float


def stamp_to_sec(stamp) -> float:
    return float(stamp.sec) + 1e-9 * float(stamp.nanosec)


def window_means(x: np.ndarray, fs: float, T: float) -> np.ndarray:
    """Non-overlapping window means of length T seconds."""
    if x.size == 0:
        return np.array([], dtype=np.float64)
    n = int(round(T * fs))
    if n <= 1:
        return np.array([], dtype=np.float64)
    m = (x.size // n) * n
    if m < n:
        return np.array([], dtype=np.float64)
    x2 = x[:m].reshape(-1, n)
    return x2.mean(axis=1)


def estimate_params(t: np.ndarray, acc: np.ndarray, gyr: np.ndarray, T_bias: float = 1.0) -> Params:
    # dt estimate
    dt_all = np.diff(t)
    dt_all = dt_all[np.isfinite(dt_all)]
    dt_all = dt_all[(dt_all > 1e-5) & (dt_all < 0.1)]
    if dt_all.size < 10:
        raise RuntimeError("Not enough valid dt samples. Check timestamps / topic / interval.")
    dt = float(np.median(dt_all))
    fs = 1.0 / dt

    def noise_density(x_axis: np.ndarray) -> float:
        d = np.diff(x_axis)
        d = d[np.isfinite(d)]
        if d.size < 10:
            return float("nan")
        sigma_d = float(np.std(d, ddof=1))
        sigma_meas = sigma_d / math.sqrt(2.0)
        return sigma_meas * math.sqrt(dt)

    def bias_rw_density(x_axis: np.ndarray) -> float:
        mu = window_means(x_axis, fs=fs, T=T_bias)
        if mu.size < 3:
            return float("nan")
        du = np.diff(mu)
        sigma_du = float(np.std(du, ddof=1))
        return sigma_du / math.sqrt(T_bias)

    acc_n = np.array([noise_density(acc[:, i]) for i in range(3)], dtype=np.float64)
    gyr_n = np.array([noise_density(gyr[:, i]) for i in range(3)], dtype=np.float64)

    acc_w = np.array([bias_rw_density(acc[:, i]) for i in range(3)], dtype=np.float64)
    gyr_w = np.array([bias_rw_density(gyr[:, i]) for i in range(3)], dtype=np.float64)

    return Params(acc_n_xyz=acc_n, gyr_n_xyz=gyr_n, acc_w_xyz=acc_w, gyr_w_xyz=gyr_w, dt=dt)


class Imu_Calibration(Node):
    def __init__(self, topic: str, t0: float, t1: float, T_bias: float):
        super().__init__("Imu_Calibration")

        if t1 <= t0:
            raise ValueError("t1 must be > t0")
        self.topic = topic
        self.t0 = float(t0)
        self.t1 = float(t1)
        self.T_bias = float(T_bias)

        self.t_start_ref: float | None = None
        self.times: List[float] = []
        self.acc: List[Tuple[float, float, float]] = []
        self.gyr: List[Tuple[float, float, float]] = []

        self.sub = self.create_subscription(Imu, topic, self.cb, qos_profile_sensor_data)

        self.get_logger().info(
            f"Listening on {topic}. Will collect samples in [{self.t0:.3f}, {self.t1:.3f}] seconds from bag start."
        )

    def cb(self, msg: Imu):
        ts = stamp_to_sec(msg.header.stamp)

        if self.t_start_ref is None:
            self.t_start_ref = ts

        t_rel = ts - self.t_start_ref

        # Collect only within [t0, t1]
        if t_rel < self.t0:
            return

        if t_rel > self.t1:
            # compute once and exit
            try:
                self.compute_and_print()
            except Exception as e:
                self.get_logger().error(f"Failed: {e}")
            rclpy.shutdown()
            return

        ax, ay, az = msg.linear_acceleration.x, msg.linear_acceleration.y, msg.linear_acceleration.z
        gx, gy, gz = msg.angular_velocity.x, msg.angular_velocity.y, msg.angular_velocity.z

        # Basic sanity (skip NaNs)
        if any(map(lambda v: not math.isfinite(v), [ax, ay, az, gx, gy, gz])):
            return

        self.times.append(t_rel)
        self.acc.append((ax, ay, az))
        self.gyr.append((gx, gy, gz))

        if len(self.times) % 2000 == 0:
            self.get_logger().info(f"Collected {len(self.times)} samples... (t_rel ~ {t_rel:.1f}s)")

    def compute_and_print(self):
        if len(self.times) < 1000:
            raise RuntimeError(f"Too few samples collected: {len(self.times)}")

        t = np.asarray(self.times, dtype=np.float64)
        acc = np.asarray(self.acc, dtype=np.float64)
        gyr = np.asarray(self.gyr, dtype=np.float64)

        p = estimate_params(t, acc, gyr, T_bias=self.T_bias)

        def fmt3(v: np.ndarray) -> str:
            return f"[{v[0]:.6e}, {v[1]:.6e}, {v[2]:.6e}]"

        # Conservative single values commonly used in configs = max(axis)
        acc_n = float(np.nanmax(p.acc_n_xyz))
        gyr_n = float(np.nanmax(p.gyr_n_xyz))
        acc_w = float(np.nanmax(p.acc_w_xyz))
        gyr_w = float(np.nanmax(p.gyr_w_xyz))

        self.get_logger().info("==== IMU param estimates (FLIGHT interval only) ====")
        self.get_logger().info(f"dt_median: {p.dt:.6f} s  (fs ~ {1.0/p.dt:.2f} Hz)")
        self.get_logger().info(f"acc_n_xyz (m/s^2/sqrt(Hz)): {fmt3(p.acc_n_xyz)}   -> use acc_n = {acc_n:.6e}")
        self.get_logger().info(f"gyr_n_xyz (rad/s/sqrt(Hz)) : {fmt3(p.gyr_n_xyz)}   -> use gyr_n = {gyr_n:.6e}")
        self.get_logger().info(f"acc_w_xyz (proxy)          : {fmt3(p.acc_w_xyz)}   -> use acc_w = {acc_w:.6e}")
        self.get_logger().info(f"gyr_w_xyz (proxy)          : {fmt3(p.gyr_w_xyz)}   -> use gyr_w = {gyr_w:.6e}")
        self.get_logger().info("Notes:")
        self.get_logger().info(f"- acc_n/gyr_n are noise density estimates from diff() over flight.")
        self.get_logger().info(f"- acc_w/gyr_w are bias-RW proxies from {self.T_bias:.2f}s window-mean drift.")
        self.get_logger().info("===============================================")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--topic", default="/camera/camera/imu", help="IMU topic name (sensor_msgs/Imu)")
    ap.add_argument("--t0", type=float, default=120.0, help="Start time (s) from bag start for FLIGHT interval")
    ap.add_argument("--t1", type=float, default=240.0, help="End time (s) from bag start for FLIGHT interval")
    ap.add_argument("--bias_window", type=float, default=1.0, help="Window length (s) for bias RW proxy")
    args = ap.parse_args()

    rclpy.init()
    node = Imu_Calibration(topic=args.topic, t0=args.t0, t1=args.t1, T_bias=args.bias_window)
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()

#python3 imu_calibration.py --topic /camera/camera/imu --t0 120 --t1 240
