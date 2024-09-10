##ROS driver for vehicle

How to build Lanhai ros driver
=====================================================================
    	1) Clone this ros package folder(XROS) to your catkin's workspace src folder
    	2) Running catkin_make to build 
	3) Add path of setup.bash to ~/.bashrc like: echo "source ~/workspace/devel/setup.bash">> ~/.bashrc	source ~/.bashrc
	4) Copy UDEV rule file(CAN2COM_HUB.rules) to system: sudo cp src/hexros/src/CAN2COM_HUB.rules /etc/udev/rules.d/
	5) Link the CAN-COM hub and turn on the vehicle
	6) Roslaunch node_vehicle.launch(hexros/launch/node_vehicle.launch)

Ros info from node
=====================================================================
	1) If open serial port failed,ros will print out:"Open serial failed"
	2) If open serial port successfully,ros will print out device name:"Serial device : xxxxx"
	3) If vehicle is offline,ros will print out:"Vehicle offline"
	4) If vehicle is online,ros will print out vehicle series name:"Vehicle online : xxxxx"
	5) If vehicle is disable or enable failed,ros will print out:"Vehicle disable"
	6) If vehicle is not in CAN mode(remoter is online and in other mode or change mode failed),ros will print out:"wrong mode"
	7) If everything is fine,ros will print out:"All clear,start to go"

Test vehicle
=====================================================================
	1) Run node_vehicle.launch successfully
	2) Do in terminal:rosrun turtlesim turtle_teleop_key
	3) Use arrow keys of keyboard to control vehicle
