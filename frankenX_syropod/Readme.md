# FrankenX Syropod

[![Syropod Banner](https://i.imgur.com/QyMTwG3.jpg "CSIRO Robotics")](https://research.csiro.au/robotics/)

A ROS package which contains configuration and launch files for the FrankenX Syropod which is a modified version of the [PhantomX Mk1 hexapod](https://www.trossenrobotics.com/phantomx-ax-hexapod-mk1.aspx) for use with [OpenSHC](https://github.com/csiro-robotics/syropod_highlevel_controller). For other legged robots, configuration files can be modified accordingly.

[![FrankenX Syropod](https://i.imgur.com/yyTnefv.gif "FrankenX Syropod")](https://research.csiro.au/robotics/our-work/research-areas/legged-robots/)

## Getting Started

If you haven't looked at the tutorials for using OpenSHC, see [OpenSHC Tutorials](https://github.com/csiro-robotics/shc_tutorials).

### Requirements

* Ubuntu 18.04 LTS
* ROS Melodic

### Dependencies

#### Base

* [Syropod High-level Controller](https://github.com/csiro-robotics/syropod_highlevel_controller):
  * `git clone https://github.com/csiro-robotics/syropod_highlevel_controller.git`
* [Syropod Remote](https://github.com/csiro-robotics/syropod_remote):
  * `git clone https://github.com/csiro-robotics/syropod_remote.git`
* [Dynamixel Motor](https://github.com/csiro-robotics/dynamixel_motor):
  * `git clone https://github.com/csiro-robotics/dynamixel_motor.git`
* [Dynamixel Joint State Publisher](https://github.com/csiro-robotics/dynamixel_joint_state_publisher):
  * `git clone https://github.com/csiro-robotics/dynamixel_joint_state_publisher.git`

#### Control Input

* [ROS Joystick](http://wiki.ros.org/joy)
  * `sudo apt-get install ros-melodic-joy`
* [RQT Reconfigure Control](https://github.com/csiro-robotics/syropod_rqt_reconfigure_control) (Optional):
  * `git clone https://github.com/csiro-robotics/syropod_rqt_reconfigure_control.git`

Instructions on the use of differing control inputs can be found at the individual repo links above.

### Installation

```bash
mkdir -p openshc_ws/src
cd openshc_ws/src
git clone https://github.com/csiro-robotics/frankenX_syropod.git
cd ..
catkin build
```

## Operation

### High-Level Control

To run the FrankenX high-level control run the following launch file with optional arguments

`roslaunch frankenX_syropod frankenX_highlevel.launch`

Below are the default values for optional high-level arguments

* FrankenX Configuration: `config:=frankenX` (loads frankenX.yaml for SHC)
* Gait Parameters: `gait:=gait` (loads gait.yaml for SHC)
* Auto-Pose Parameters: `auto_pose:=auto_pose` (loads auto_pose.yaml for SHC)
* Control input method: `control:=joy` ('rqt' to use rqt_reconfigure_control)
* RVIZ Visualisation: `rviz:=false`
* Gazebo Simulation: `gazebo:=false` (NOTE: Currently not supported for FrankenX. No urdf model available)
* RQT Plot: `plot:=false`
* RQT Reconfigure: `reconfigure:=false`
* Auto-Logging: `logging:=false`

Tuning of configuration parameters is done using the corresponding config yaml files.
Consult [`syropod_highlevel_controller/config/readme.md`](https://github.com/csiro-robotics/syropod_highlevel_controller/tree/master/config) for details.

### Typical Usage

RVIZ Visualisation of FrankenX with hardware for debugging:

```bash
roslaunch frankenX_syropod frankenX_hardware.launch
roslaunch frankenX_syropod frankenX_highlevel.launch rviz:=true
```

Launch FrankenX as a robot:

`roslaunch frankenX_syropod frankenX_start.launch`

## Authors

* Oshada Jayasinghe
* Benjamin Tam

## License

This project is licensed under the CSIRO Open Source Software Licence Agreement (variation of the BSD / MIT License) - see the [LICENSE](LICENSE) file for details.

## Issues

Please report bugs using [Issue Tracker](https://github.com/csiro-robotics/frankenX_syropod/issues) or contact us via email [shc-support@csiro.au](mailto:shc-support@csiro.au).
