/*******************************************************
 * Copyright (C) 2019, Aerial Robotics Group, Hong Kong University of Science and Technology
 * 
 * This file is part of VINS.
 * 
 * Licensed under the GNU General Public License v3.0;
 * you may not use this file except in compliance with the License.
 *******************************************************/

#pragma once

#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <eigen3/Eigen/Dense>
#include "../utility/utility.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <fstream>
#include <map>

using namespace std;

#define ROS_INFO RCUTILS_LOG_INFO
#define ROS_WARN RCUTILS_LOG_WARN
#define ROS_ERROR RCUTILS_LOG_ERROR

const double FOCAL_LENGTH = 460.0;
const int WINDOW_SIZE = 10;
const int NUM_OF_F = 1000;
//#define UNIT_SPHERE_ERROR

extern double INIT_DEPTH;
extern double MIN_PARALLAX;
extern int ESTIMATE_EXTRINSIC;

extern int USE_GPU;
extern int USE_GPU_ACC_FLOW;
extern int USE_GPU_CERES;

extern double ACC_N, ACC_W;
extern double GYR_N, GYR_W;

extern std::vector<Eigen::Matrix3d> RIC;
extern std::vector<Eigen::Vector3d> TIC;
extern Eigen::Vector3d G;

extern double BIAS_ACC_THRESHOLD;
extern double BIAS_GYR_THRESHOLD;
extern double SOLVER_TIME;
extern int NUM_ITERATIONS;
extern std::string EX_CALIB_RESULT_PATH;
extern std::string VINS_RESULT_PATH;
extern std::string OUTPUT_FOLDER;
extern std::string IMU_TOPIC;
extern double TD;
extern int ESTIMATE_TD;
extern int ROLLING_SHUTTER;
extern int ROW, COL;
extern int NUM_OF_CAM;
extern int STEREO;
extern int USE_IMU;
extern int MULTIPLE_THREAD;
// pts_gt for debug purpose;
extern map<int, Eigen::Vector3d> pts_gt;

extern std::string IMAGE0_TOPIC, IMAGE1_TOPIC;
extern std::string FISHEYE_MASK;
extern std::vector<std::string> CAM_NAMES;
extern int MAX_CNT;
extern int MIN_DIST;
extern double F_THRESHOLD;
extern int SHOW_TRACK;
extern int FLOW_BACK;
extern std::string WORLD_FRAME_ID;
extern std::string BODY_FRAME_ID;
extern std::string CAMERA_FRAME_ID;

// Visual feature gate: prevents low-quality visual data from entering the
// backend optimizer (and therefore the marginalization prior) when tracking
// degrades. Closes instantly on a single bad frame; reopens only after
// several consecutive frames where all three tracking signals recover.
extern int VISUAL_GATE_CLOSE_THRESH;       // backend feature count below which the gate closes immediately
extern int VISUAL_GATE_REOPEN_LAST_TRACK;  // required last_track_num to count this frame as healthy
extern int VISUAL_GATE_REOPEN_LONG_TRACK;  // required long_track_num to count this frame as healthy
extern int VISUAL_GATE_REOPEN_BACKEND;     // required backend feature count to count this frame as healthy
extern int VISUAL_GATE_REOPEN_CONSECUTIVE; // consecutive healthy frames required before reopening

// Local relocalization bank (Part 3): short-horizon self-landmarks that
// anchor pose while the visual feature gate is closed. Only ever engages
// with enough RANSAC-verified inliers -- see LOCAL_MAP_MIN_INLIERS.
extern int LOCAL_MAP_BANK_MAX_SIZE;      // ring buffer capacity (descriptors)
extern int LOCAL_MAP_MIN_BANK_SIZE;      // don't attempt matching below this
extern int LOCAL_MAP_MAX_HAMMING_DIST;   // per-match ORB Hamming distance cutoff (max 256)
extern int LOCAL_MAP_MIN_MATCHES;        // minimum raw matches before attempting PnP-RANSAC
extern int LOCAL_MAP_MIN_INLIERS;        // minimum RANSAC inliers before trusting the result at all
extern double LOCAL_MAP_PNP_REPROJ_ERROR; // RANSAC reprojection threshold, in normalized-ray units
extern int LOCAL_MAP_ENABLE; // master switch -- 0 disables bank population and relocalization entirely
extern double LOCAL_MAP_JUMP_GATE_M; // reject relocalization if disambiguated pose disagrees with IMU-propagated prediction by more than this (meters)

// Gyroscope bias initial-calibration conditioning check (initial_alignment.cpp).
// Ratio of smallest/largest eigenvalue of the 3x3 normal-equations matrix;
// too low means the init window lacked genuine multi-axis rotation and the
// solved delta_bg shouldn't be trusted.
extern double GYRO_BIAS_MIN_COND_RATIO;

void readParameters(std::string config_file);

enum SIZE_PARAMETERIZATION
{
    SIZE_POSE = 7,
    SIZE_SPEEDBIAS = 9,
    SIZE_FEATURE = 1
};

enum StateOrder
{
    O_P = 0,
    O_R = 3,
    O_V = 6,
    O_BA = 9,
    O_BG = 12
};

enum NoiseOrder
{
    O_AN = 0,
    O_GN = 3,
    O_AW = 6,
    O_GW = 9
};