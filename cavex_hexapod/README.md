# CaveX Hexapod

This repo is a ROS Rviz and Gazebo simulation of the CaveX Hexapod using OpenSHC gait control. It was modified from the CSIRO's csiro-robotics/bullet_syropod repository https://github.com/csiro-robotics/bullet_syropod. It contains the configuration, model and launch files specific to the CaveX robot.

## Requirements

* Ubuntu 18.04 LTS
* ROS Melodic

## Dependencies

### Base

* [Syropod High-level Controller](https://github.com/csiro-robotics/syropod_highlevel_controller):
  * `git clone https://github.com/csiro-robotics/syropod_highlevel_controller.git`
* [Syropod Remote](https://github.com/csiro-robotics/syropod_remote):
  * `git clone https://github.com/csiro-robotics/syropod_remote.git`

### Control Input

* [ROS Joystick](http://wiki.ros.org/joy)
  * `sudo apt-get install ros-melodic-joy`
* [RQT Reconfigure Control](https://github.com/csiro-robotics/syropod_rqt_reconfigure_control) (Optional):
  * `git clone https://github.com/csiro-robotics/syropod_rqt_reconfigure_control.git`


## Issues

The foot tips are slipping, and the robot does not move in specified positive x-direction. Leg movements seem to be "cancelling out" due to hexagonal symmetry.
![Gazebo](https://i.imgur.com/odcmgon.gif)

The robot is not spawning in Rviz properly. Also, there is a mismatch between the coordinates in Gazebo and RViz (see the foot tip positions).

![Rviz](https://i.imgur.com/AkRELXb.png)

## Usage

For detailed setup and operation instructions, see the bullet_syropod README.md on their page.

I have setup the launch/config files so that this command runs the gazebo simulation as desired: roslaunch cavex_hexapod hexapod_highlevel.launch gazebo:=true

## Authors

Original:
* Samith Ashan
* Benjamin Tam

Modified by:
* Matthew King

## License

This project is licensed under the CSIRO Open Source Software Licence Agreement (variation of the BSD / MIT License) - see the [LICENSE](LICENSE) file for details.
