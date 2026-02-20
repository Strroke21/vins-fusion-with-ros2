#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np
import argparse
import time
import os

from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

pattern_size = (8,5)

class Calibrator(Node):

    def __init__(self, topic, square, num, width, height, yaml_path):

        super().__init__('video_calibrator')

        self.bridge = CvBridge()
        self.square = square
        self.num = num
        self.req_width = width
        self.req_height = height
        self.yaml_path = yaml_path

        qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )

        self.sub = self.create_subscription(
            Image,
            topic,
            self.callback,
            qos
        )

        self.objp = np.zeros((pattern_size[0]*pattern_size[1],3), np.float32)
        self.objp[:,:2] = np.indices(pattern_size).T.reshape(-1,2)
        self.objp *= self.square

        self.objpoints = []
        self.imgpoints = []

        self.count = 0
        self.last_capture_time = 0
        self.capture_delay = 0.5

        self.criteria = (cv2.TERM_CRITERIA_EPS +
                         cv2.TERM_CRITERIA_MAX_ITER,
                         30,0.001)

        print("\nMove chessboard slowly across FOV...\n")

    def callback(self,msg):

        frame = self.bridge.imgmsg_to_cv2(msg,'mono8')

        if frame.shape[1] != self.req_width or frame.shape[0] != self.req_height:
            return

        ret,corners = cv2.findChessboardCorners(
            frame,
            pattern_size,
            cv2.CALIB_CB_ADAPTIVE_THRESH +
            cv2.CALIB_CB_NORMALIZE_IMAGE
        )

        if ret:

            corners2 = cv2.cornerSubPix(
                frame,corners,(11,11),(-1,-1),
                self.criteria
            )

            cv2.drawChessboardCorners(frame,
                                      pattern_size,
                                      corners2,
                                      ret)

            if (time.time() - self.last_capture_time) > self.capture_delay:
                self.objpoints.append(self.objp)
                self.imgpoints.append(corners2)
                self.count += 1
                self.last_capture_time = time.time()
                print(f"Captured {self.count}/{self.num}")

        cv2.imshow("Calibration",frame)
        cv2.waitKey(1)

        if self.count >= self.num:
            self.calibrate(frame.shape[::-1])
            rclpy.shutdown()

    def calibrate(self,size):

        ret,K,D,_,_ = cv2.calibrateCamera(
            self.objpoints,
            self.imgpoints,
            size,
            None,
            None
        )

        fx = K[0,0]
        fy = K[1,1]
        cx = K[0,2]
        cy = K[1,2]

        k1 = D[0][0]
        k2 = D[0][1]
        p1 = D[0][2]
        p2 = D[0][3]

        os.makedirs(os.path.dirname(self.yaml_path),exist_ok=True)

        with open(self.yaml_path,'w') as f:
            f.write(f"""%YAML:1.0
---
model_type: PINHOLE
camera_name: camera
image_width: {size[0]}
image_height: {size[1]}
distortion_parameters:
   k1: {k1}
   k2: {k2}
   p1: {p1}
   p2: {p2}
projection_parameters:
   fx: {fx}
   fy: {fy}
   cx: {cx}
   cy: {cy}""")

        print(f"\nSaved to: {self.yaml_path}\n")
        print((f"""%YAML:1.0
---
model_type: PINHOLE
camera_name: camera
image_width: {size[0]}
image_height: {size[1]}
distortion_parameters:
   k1: {k1}
   k2: {k2}
   p1: {p1}
   p2: {p2}
projection_parameters:
   fx: {fx}
   fy: {fy}
   cx: {cx}
   cy: {cy}"""))
        

def main():

    parser = argparse.ArgumentParser()

    parser.add_argument('--topic',required=True)
    parser.add_argument('--square',type=float,required=True)
    parser.add_argument('--num',type=int,required=True)
    parser.add_argument('--width',type=int,required=True)
    parser.add_argument('--height',type=int,required=True)
    parser.add_argument('--yaml',required=True)

    args = parser.parse_args()

    rclpy.init()

    node = Calibrator(
        args.topic,
        args.square,
        args.num,
        args.width,
        args.height,
        args.yaml
    )

    rclpy.spin(node)

if __name__=="__main__":
    main()