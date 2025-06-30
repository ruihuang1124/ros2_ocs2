# OCS2_ROS2 Toolbox

Tested on Ubuntu 22.04 ROS2 Humble.

## 1 Dependency

* C++ compiler with C++17 support
* Eigen (v3.4)
* Boost C++ (v1.74)
* pinocchio (up-to-date)

## 2 Installation

The OCS2 library is written in C++17. It is tested under Ubuntu with library versions as provided in the package
sources.

### 2.1 Install Dependency

* Eigen

```bash
sudo apt update
sudo apt install libeigen3-dev 
sudo apt-get install ros-humble-grid-map-cv ros-humble-grid-map-msgs ros-humble-grid-map-ros ros-humble-grid-map-sdf ros-humble-octomap libmpfr-dev libpcap-dev libglpk-dev libglfw3-dev
```

### 2.3 Clone Repositories

* Create a new workspace or clone the project to your workspace

```bash
cd ~
mkdir -p colcon_ws/src
```

* Clone the repository

```bash
cd ~/colcon_ws/src
# Clone ocs2_ros2
git clone https://github.com/ruihuang1124/ros2_ocs2.git
# Clone pinocchio
git clone --recurse-submodules https://github.com/ruihuang1124/pinocchio.git
# Clone hpp-fcl
git clone --recurse-submodules https://github.com/ruihuang1124/hpp-fcl.git
```

* build

```bash
cd ~/colcon_ws
colcon build --packages-up-to ocs2_legged_robot_ros ocs2_self_collision_visualization --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo
```

## 3 Run Example

* Run the legged robot example
```bash
source ~/colcon_ws/install/setup.bash
ros2 launch ocs2_legged_robot_ros legged_robot_sqp.launch.py
```

