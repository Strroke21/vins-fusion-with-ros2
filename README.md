
# VINS-Fusion (GPU enabled)

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
  -DCMAKE_BUILD_TYPE=Release

make -j$(nproc)
sudo make install
sudo ldconfig

```

### Install Opencv with CUDA (Essential)
```
git clone https://github.com/opencv/opencv_contrib/
cd opencv_contrib
git checkout 4.10.0
cd ..
git clone https://github.com/opencv/opencv/
cd opencv
git checkout 4.10.0
mkdir build/
cd build/

cmake \
-D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_CUDA=ON \
-D CUDA_ARCH_BIN=8.7 \
-D CUDA_ARCH_PTX="" \
-D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
-D WITH_CUDNN=ON \
-D OPENCV_DNN_CUDA=ON \
-D ENABLE_FAST_MATH=1 \
-D CUDA_FAST_MATH=1 \
..

# CUDA_ARCH_BIN=8.9 for x86 arch
# CUDA_ARCH_BIN=8.7 for ARM arch

make -j4
sudo make install

```

### Install ROS2-Humble

https://github.com/Strroke21/V-SLAM-with-RTABMAP-and-Realsense-D4XX


### clone the repo

``` cd (your workspace)/src

git clone https://github.com/Strroke21/vins-fusion-with-ros2

cd vins-fusion-with-ros2

colcon build 

echo "source /opt/ros/humble/bin/ros2" >> ~/.bashrc
echo "source ~/vins-fusion-with-ros2/install/setup.bash" >> ~/.bashrc
source ~/.bashrc

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

ros2 run vins vins_node ~/vins-fusion-with-ros2/custom_config/rs_d455/rs_d455.yaml

ros2 run loop_fusion loop_fusion_node ~/vins-fusion-ros2/custom_config/rs_d455/rs_d455.yaml #optional for loop closure

rviz2 -d ~/vins-fusion-with-ros2/custom_config/vins_fusion.rviz

#optional for visualization

```

### for ardupilot 

``` 
python3 aero_vins.py #update in progress 

```
### Flight Test Video

[![Watch the video](SLAM.png)](https://drive.google.com/file/d/1Q1i9fy6b75TaGaKeJ7mhqQjBl9eKBurt/preview)