# ball-chaser
This repository simulates a diff drive robot in Gazebo equipped with a camera and LiDAR sensor that follows white balls

The gazebo environment is a simulation of my apartment. You can pick and place the white ball anywhere in the apartment and if it is in the field of view of the robot's camera, then the robot will go towards it.

![screenshots](/SS_1_Ball_Chaser.png)

This repo is the src directory of the catkin_ws. You will need to install ROS-Kinetic, Gazebo and the Rviz plugins to run the code succesfully. After that, navigate to the folder containing the repo (rename it src) and run the following commands on a terminal:
```
$ mkdir catkin_ws
$ mv src catkin_ws/src
$ cd catkin_ws/src
$ catkin_init_workspace
$ cd ..
$ catkin_make
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

In another terminal, navigate to the catkin_ws folder

```
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```
