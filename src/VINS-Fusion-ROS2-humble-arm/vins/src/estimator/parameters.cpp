/*******************************************************
 * Copyright (C) 2019, Aerial Robotics Group, Hong Kong University of Science and Technology
 * 
 * This file is part of VINS.
 * 
 * Licensed under the GNU General Public License v3.0;
 * you may not use this file except in compliance with the License.
 *******************************************************/

#include "parameters.h"

double INIT_DEPTH;
double MIN_PARALLAX;
double ACC_N, ACC_W;
double GYR_N, GYR_W;

std::vector<Eigen::Matrix3d> RIC;
std::vector<Eigen::Vector3d> TIC;

Eigen::Vector3d G{0.0, 0.0, 9.8};

int USE_GPU;
int USE_GPU_ACC_FLOW;
int USE_GPU_CERES;

double BIAS_ACC_THRESHOLD;
double BIAS_GYR_THRESHOLD;
double SOLVER_TIME;
int NUM_ITERATIONS;
int ESTIMATE_EXTRINSIC;
int ESTIMATE_TD;
int ROLLING_SHUTTER;
std::string EX_CALIB_RESULT_PATH;
std::string VINS_RESULT_PATH;
std::string OUTPUT_FOLDER;
std::string IMU_TOPIC;
int ROW, COL;
double TD;
int NUM_OF_CAM;
int STEREO;
int USE_IMU;
int MULTIPLE_THREAD;
map<int, Eigen::Vector3d> pts_gt;
std::string IMAGE0_TOPIC, IMAGE1_TOPIC;
std::string FISHEYE_MASK;
std::vector<std::string> CAM_NAMES;
int MAX_CNT;
int MIN_DIST;
double F_THRESHOLD;
int SHOW_TRACK;
int FLOW_BACK;

std::string WORLD_FRAME_ID;
std::string BODY_FRAME_ID;
std::string CAMERA_FRAME_ID;

int VISUAL_GATE_CLOSE_THRESH;
int VISUAL_GATE_REOPEN_LAST_TRACK;
int VISUAL_GATE_REOPEN_LONG_TRACK;
int VISUAL_GATE_REOPEN_BACKEND;
int VISUAL_GATE_REOPEN_CONSECUTIVE;

int LOCAL_MAP_BANK_MAX_SIZE;
int LOCAL_MAP_MIN_BANK_SIZE;
int LOCAL_MAP_MAX_HAMMING_DIST;
int LOCAL_MAP_MIN_MATCHES;
int LOCAL_MAP_MIN_INLIERS;
double LOCAL_MAP_PNP_REPROJ_ERROR;
int LOCAL_MAP_ENABLE;
double LOCAL_MAP_JUMP_GATE_M;
double GYRO_BIAS_MIN_COND_RATIO;

template <typename T>
T readParam(rclcpp::Node::SharedPtr n, std::string name)
{
    T ans;
    if (n->get_parameter(name, ans))
    {
        ROS_INFO("Loaded %s: ", name);
        std::cout << ans << std::endl;
    }
    else
    {
        ROS_ERROR("Failed to load %s", name);
        rclcpp::shutdown();
    }
    return ans;
}

void readParameters(std::string config_file)
{
    FILE *fh = fopen(config_file.c_str(),"r");
    if(fh == NULL){
        ROS_WARN("config_file dosen't exist; wrong config_file path");
        // ROS_BREAK();
        return;          
    }
    fclose(fh);

    cv::FileStorage fsSettings(config_file, cv::FileStorage::READ);
    if(!fsSettings.isOpened())
    {
        std::cerr << "ERROR: Wrong path to settings" << std::endl;
    }

    fsSettings["image0_topic"] >> IMAGE0_TOPIC;
    fsSettings["image1_topic"] >> IMAGE1_TOPIC;
    MAX_CNT = fsSettings["max_cnt"];
    MIN_DIST = fsSettings["min_dist"];
    F_THRESHOLD = fsSettings["F_threshold"];
    SHOW_TRACK = fsSettings["show_track"];
    FLOW_BACK = fsSettings["flow_back"];

    MULTIPLE_THREAD = fsSettings["multiple_thread"];

    USE_GPU = fsSettings["use_gpu"];
    USE_GPU_ACC_FLOW = fsSettings["use_gpu_acc_flow"];
    USE_GPU_CERES = fsSettings["use_gpu_ceres"];

    USE_IMU = fsSettings["imu"];
    printf("USE_IMU: %d\n", USE_IMU);
    if(USE_IMU)
    {
        fsSettings["imu_topic"] >> IMU_TOPIC;
        printf("IMU_TOPIC: %s\n", IMU_TOPIC.c_str());
        ACC_N = fsSettings["acc_n"];
        ACC_W = fsSettings["acc_w"];
        GYR_N = fsSettings["gyr_n"];
        GYR_W = fsSettings["gyr_w"];
        G.z() = fsSettings["g_norm"];
    }

    SOLVER_TIME = fsSettings["max_solver_time"];
    NUM_ITERATIONS = fsSettings["max_num_iterations"];
    MIN_PARALLAX = fsSettings["keyframe_parallax"];
    MIN_PARALLAX = MIN_PARALLAX / FOCAL_LENGTH;

    fsSettings["output_path"] >> OUTPUT_FOLDER;
    VINS_RESULT_PATH = OUTPUT_FOLDER + "/vio.csv";
    std::cout << "result path " << VINS_RESULT_PATH << std::endl;
    std::ofstream fout(VINS_RESULT_PATH, std::ios::out);
    fout.close();

    ESTIMATE_EXTRINSIC = fsSettings["estimate_extrinsic"];
    if (ESTIMATE_EXTRINSIC == 2)
    {
        ROS_WARN("have no prior about extrinsic param, calibrate extrinsic param");
        RIC.push_back(Eigen::Matrix3d::Identity());
        TIC.push_back(Eigen::Vector3d::Zero());
        EX_CALIB_RESULT_PATH = OUTPUT_FOLDER + "/extrinsic_parameter.csv";
    }
    else 
    {
        if ( ESTIMATE_EXTRINSIC == 1)
        {
            ROS_WARN(" Optimize extrinsic param around initial guess!");
            EX_CALIB_RESULT_PATH = OUTPUT_FOLDER + "/extrinsic_parameter.csv";
        }
        if (ESTIMATE_EXTRINSIC == 0)
            ROS_WARN(" fix extrinsic param ");

        cv::Mat cv_T;
        fsSettings["body_T_cam0"] >> cv_T;
        Eigen::Matrix4d T;
        cv::cv2eigen(cv_T, T);
        RIC.push_back(T.block<3, 3>(0, 0));
        TIC.push_back(T.block<3, 1>(0, 3));
    } 
    
    NUM_OF_CAM = fsSettings["num_of_cam"];
    printf("camera number %d\n", NUM_OF_CAM);

    if(NUM_OF_CAM != 1 && NUM_OF_CAM != 2)
    {
        printf("num_of_cam should be 1 or 2\n");
        assert(0);
    }


    int pn = config_file.find_last_of('/');
    std::string configPath = config_file.substr(0, pn);
    
    std::string cam0Calib;
    fsSettings["cam0_calib"] >> cam0Calib;
    std::string cam0Path = configPath + "/" + cam0Calib;
    CAM_NAMES.push_back(cam0Path);

    if(NUM_OF_CAM == 2)
    {
        STEREO = 1;
        std::string cam1Calib;
        fsSettings["cam1_calib"] >> cam1Calib;
        std::string cam1Path = configPath + "/" + cam1Calib; 
        //printf("%s cam1 path\n", cam1Path.c_str() );
        CAM_NAMES.push_back(cam1Path);
        
        cv::Mat cv_T;
        fsSettings["body_T_cam1"] >> cv_T;
        Eigen::Matrix4d T;
        cv::cv2eigen(cv_T, T);
        RIC.push_back(T.block<3, 3>(0, 0));
        TIC.push_back(T.block<3, 1>(0, 3));
    }

    INIT_DEPTH = 5.0;
    BIAS_ACC_THRESHOLD = 0.1;
    BIAS_GYR_THRESHOLD = 0.1;

    TD = fsSettings["td"];
    ESTIMATE_TD = fsSettings["estimate_td"];
    if (ESTIMATE_TD)
        ROS_INFO("Unsynchronized sensors, online estimate time offset, initial td: %f", TD);
    else
        ROS_INFO("Synchronized sensors, fix time offset: %f", TD);

    ROW = fsSettings["image_height"];
    COL = fsSettings["image_width"];
    ROS_INFO("ROW: %d COL: %d ", ROW, COL);

    if(!USE_IMU)
    {
        ESTIMATE_EXTRINSIC = 0;
        ESTIMATE_TD = 0;
        printf("no imu, fix extrinsic param; no time offset calibration\n");
    }

    fsSettings["world_frame_id"] >> WORLD_FRAME_ID;
    WORLD_FRAME_ID.empty()? WORLD_FRAME_ID = "world" : WORLD_FRAME_ID;
    fsSettings["body_frame_id"] >> BODY_FRAME_ID;   
    BODY_FRAME_ID.empty()? BODY_FRAME_ID = "body" : BODY_FRAME_ID;
    fsSettings["camera_frame_id"] >> CAMERA_FRAME_ID;
    CAMERA_FRAME_ID.empty()? CAMERA_FRAME_ID = "camera" : CAMERA_FRAME_ID;
    
    ROS_INFO("frame_ids: world=%s body=%s camera=%s", WORLD_FRAME_ID.c_str(),
             BODY_FRAME_ID.c_str(), CAMERA_FRAME_ID.c_str());

    // Visual feature gate thresholds. Defaults chosen so existing config
    // files that don't have these keys yet still work; override in YAML
    // once tuned against real flight logs.
    cv::FileNode gateCloseNode = fsSettings["visual_gate_close_thresh"];
    VISUAL_GATE_CLOSE_THRESH = gateCloseNode.empty() ? 80 : (int)gateCloseNode;

    cv::FileNode gateLastTrackNode = fsSettings["visual_gate_reopen_last_track"];
    VISUAL_GATE_REOPEN_LAST_TRACK = gateLastTrackNode.empty() ? 20 : (int)gateLastTrackNode;

    cv::FileNode gateLongTrackNode = fsSettings["visual_gate_reopen_long_track"];
    VISUAL_GATE_REOPEN_LONG_TRACK = gateLongTrackNode.empty() ? 40 : (int)gateLongTrackNode;

    cv::FileNode gateBackendNode = fsSettings["visual_gate_reopen_backend"];
    VISUAL_GATE_REOPEN_BACKEND = gateBackendNode.empty() ? VISUAL_GATE_CLOSE_THRESH : (int)gateBackendNode;

    cv::FileNode gateConsecutiveNode = fsSettings["visual_gate_reopen_consecutive"];
    VISUAL_GATE_REOPEN_CONSECUTIVE = gateConsecutiveNode.empty() ? 5 : (int)gateConsecutiveNode;

    ROS_INFO("visual gate: close<%d  reopen(last>=%d, long>=%d, backend>=%d for %d consecutive frames)",
             VISUAL_GATE_CLOSE_THRESH, VISUAL_GATE_REOPEN_LAST_TRACK, VISUAL_GATE_REOPEN_LONG_TRACK,
             VISUAL_GATE_REOPEN_BACKEND, VISUAL_GATE_REOPEN_CONSECUTIVE);

    cv::FileNode bankMaxNode = fsSettings["local_map_bank_max_size"];
    LOCAL_MAP_BANK_MAX_SIZE = bankMaxNode.empty() ? 500 : (int)bankMaxNode;

    cv::FileNode bankMinNode = fsSettings["local_map_min_bank_size"];
    LOCAL_MAP_MIN_BANK_SIZE = bankMinNode.empty() ? 30 : (int)bankMinNode;

    cv::FileNode hammingNode = fsSettings["local_map_max_hamming_dist"];
    LOCAL_MAP_MAX_HAMMING_DIST = hammingNode.empty() ? 50 : (int)hammingNode;

    cv::FileNode minMatchNode = fsSettings["local_map_min_matches"];
    LOCAL_MAP_MIN_MATCHES = minMatchNode.empty() ? 10 : (int)minMatchNode;

    cv::FileNode minInlierNode = fsSettings["local_map_min_inliers"];
    LOCAL_MAP_MIN_INLIERS = minInlierNode.empty() ? 8 : (int)minInlierNode;

    cv::FileNode reprojNode = fsSettings["local_map_pnp_reproj_error"];
    LOCAL_MAP_PNP_REPROJ_ERROR = reprojNode.empty() ? 0.01 : (double)reprojNode;

    cv::FileNode enableNode = fsSettings["local_map_enable"];
    LOCAL_MAP_ENABLE = enableNode.empty() ? 1 : (int)enableNode;

    cv::FileNode jumpGateNode = fsSettings["local_map_jump_gate_m"];
    LOCAL_MAP_JUMP_GATE_M = jumpGateNode.empty() ? 5.0 : (double)jumpGateNode;

    cv::FileNode gyroBiasCondNode = fsSettings["gyro_bias_min_cond_ratio"];
    GYRO_BIAS_MIN_COND_RATIO = gyroBiasCondNode.empty() ? 0.01 : (double)gyroBiasCondNode;

    ROS_INFO("local map bank: enabled=%d max_size=%d min_size=%d hamming<%d min_matches=%d min_inliers=%d reproj_err=%f jump_gate_m=%f",
             LOCAL_MAP_ENABLE, LOCAL_MAP_BANK_MAX_SIZE, LOCAL_MAP_MIN_BANK_SIZE, LOCAL_MAP_MAX_HAMMING_DIST,
             LOCAL_MAP_MIN_MATCHES, LOCAL_MAP_MIN_INLIERS, LOCAL_MAP_PNP_REPROJ_ERROR, LOCAL_MAP_JUMP_GATE_M);
    ROS_INFO("gyro bias min condition ratio: %f", GYRO_BIAS_MIN_COND_RATIO);

    fsSettings.release();
}