# CaveX Hexapod

This repository was modified from the CSIRO's csiro-robotics/bullet_syropod repository https://github.com/csiro-robotics/bullet_syropod. It contains the configuration, model and launch files specific to the CaveX robot.

CaveX is a Mechanical Engineering Honours Group at the University of Adelaide, South Australia. We have designed and are building a semi-autonomous robot for mapping cave systems such as the Naracoorte Cavex using SLAM and LiDAR. We are using a Velodyne PUCK, Dynamixel XL servos and a Jetson Nano and OpenCR1.0 control boards.

Here is the beautiful Alexandra Cave with active formations.
![Naracoorte Caves](https://i.imgur.com/5aG7TQX.jpg)

Here's the team doing a scan.
[Scanning](https://i.imgur.com/souMcaw.jpg)

Here's the Naracoorte Cave system map courtesy of Craig Williams (UofA) that we are aiming to contribute to.
[Cave Map](https://i.imgur.com/kqwxnCC.png)

## Issues

The foot tips are slipping, and the robot does not move in specified positive x-direction. Leg movements seem to be "cancelling out" due to hexagonal symmetry.
[Gazebo](https://i.imgur.com/odcmgon.gif)

The robot is not spawning in Rviz properly. Also, there is a mismatch between the coordinates in Gazebo and RViz (see the foot tip positions).

[Rviz](https://i.imgur.com/AkRELXb.png)

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
