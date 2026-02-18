
# VINS-Fusion

## VINS-Fusion with ROS2-Humble

### Prerequisites

- **System**
  - Ubuntu 22.04
  - ROS2 Humble

### Install Ceres-Solver with CUDA
#### Install dependencies
``` 
sudo apt install -y \
  cmake \
  git \
  libgoogle-glog-dev \
  libgflags-dev \
  libatlas-base-dev \
  libsuitesparse-dev \
  libeigen3-dev

```
#### Clone Ceres Solver

``` 
cd ~
git clone https://github.com/ceres-solver/ceres-solver.git
cd ceres-solver
git checkout 2.1.0   # recommended stable

```

#### Configure with CUDA ENABLED

```
mkdir build && cd build

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCERES_USE_CUDA=ON \
  -DCERES_USE_OPENMP=ON \
  -DBUILD_TESTING=OFF \
  -DBUILD_EXAMPLES=OFF

make -j$(nproc)
sudo make install
sudo ldconfig

```

### Install Opencv 
```
git clone https://github.com/opencv/opencv_contrib/
cd opencv_contrib
git checkout 4.10.0
cd ..
git clone https://github.com/opencv/opencv/
cd opencv
git checkout 4.10.0
mkdir opencv/build/
cd opencv/build/

cmake \
-D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_CUDA=ON \
-D BUILD_TESTS=OFF \
-D BUILD_PERF_TESTS=OFF \
-D OPENCV_DNN_CUDA=OFF \
-D CUDA_ARCH_BIN=8.9 \
-D CUDA_NVCC_FLAGS="--expt-relaxed-constexpr" \
-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
..

make -j8
sudo make install

```

### Install ROS2-Humble

https://github.com/Strroke21/V-SLAM-with-RTABMAP-and-Realsense-D4XX


### clone the repo

``` cd (your workspace)/src

git clone https://github.com/JanekDev/VINS-Fusion-ROS2-humble-arm

cd ..
 colcon build   --cmake-args   -DCMAKE_PREFIX_PATH=/usr/local   -DOpenCV_DIR=/usr/local/lib/cmake/opencv4   -DCMAKE_BUILD_TYPE=Release

source install/setup.bash && source install/setup.sh

```
### Run the Node (for dataset)

``` 
ros2 bag play (dataset folder) 
ros2 run vins vins_node (your config path)
ros2 launch vins vins_rviz.launch.xml

```
### for camera (realsense)

```
ros2 launch realsense2_camera rs_launch.py \
enable_infra1:=true enable_infra2:=true enable_color:=true enable_sync:=true \
rgb_camera.color_profile:=640,480,30 \
enable_sync:=true enable_gyro:=true enable_accel:=true \
unite_imu_method:=2 gyro_fps:=200 accel_fps:=200 \
depth_module.infra_profile:=640,480,90

ros2 run vins vins_node /home/deathstroke/vins-fusion-ros2/src/VINS-Fusion-ROS2-humble-arm/config/realsense_d435i/realsense_stereo_imu_config.yaml

ros2 run loop_fusion loop_fusion_node /home/deathstroke/vins-fusion-ros2/src/VINS-Fusion-ROS2-humble-arm/config/realsense_d435i/realsense_stereo_imu_config.yaml #optional for loop closure

ros2 launch rtabmap_launch rtabmap.launch.py     rtabmap_args:="--delete_db_on_start"     rgb_topic:=/camera/camera/color/image_raw     camera_info_topic:=/camera/camera/color/camera_info     odom_topic:=/odometry     approx_sync:=true     depth:=false     visual_odometry:=false 

#optional for visualization

```

### for ardupilot 

``` 
python3 aero_vins.py 

```
