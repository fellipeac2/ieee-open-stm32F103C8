# IEEE-OPEN-MBED

## Prerequisites:

- Git installed
- Ros and Catkin installed in your pc
- Clone and install gcc4mbed
- Install rosserial package
- Set some environment variables

## GCC4mbed

Clone gcc4mbed from https://github.com/adamgreen/gcc4mbed into $HOME directory
- first in your $HOME directory match the following command:
  git clone https://github.com/adamgreen/gcc4mbed
- second enter in gcc4mbed:
  cd gcc4mbed
- install gcc4mbed for linux:
  ./linux_install
- wait finish

## ROSSERIAL

Download and install rossserial
- enter in ~/catkin_ws/src directory
  cd ~/catkin_ws/src/
- clone the repo here:
  git clone https://github.com/ros-drivers/rosserial.git
- wait for it and after get back into ~/catkin_ws directory
- compile ros packages:
  catkin_make
- set the environment:
  source devel/setup.bash
- run the following command:
  rosrun rosserial_mbed make_libraries.py ~/ros/lib
- done!

Set some environment variables
  - export GCC4MBED_DIR=~/gcc4mbed
  - export ROS_LIB_DIR=~/ros/lib/ros_lib
  
## COMPILE

- run make
- copy rosserial_step_motor_open.bin to mbed

#done!

## Refs.:
http://wiki.ros.org/rosserial_mbed/Tutorials/rosserial_mbed%20Setup
