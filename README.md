
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
### clone the repo

``` cd (your workspace)/src

git clone https://github.com/JanekDev/VINS-Fusion-ROS2-humble-arm

cd ..
colcon build
source install/setup.bash && source install/setup.sh

```
### Run the Node

``` 
ros2 bag play (dataset folder) or camera node
ros2 run vins vins_node (your config path)

```
