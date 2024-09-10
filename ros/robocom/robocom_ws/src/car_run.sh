#!/bin/bash

# 打开第一个终端并运行命令1
gnome-terminal --tab --title="Bringup" --command="bash -c 'roslaunch xpkg_bringup bringup_basic_ctrl.launch; $SHELL'"

# 等待一段时间，确保上一个命令已经执行完毕
sleep 5

# 打开第二个终端并运行命令2
gnome-terminal --tab --title="USB Cam" --command="bash -c 'roslaunch usb_cam usb_cam-test.launch; $SHELL'"

# 等待一段时间，确保上一个命令已经执行完毕
sleep 5

# 打开第三个终端并运行命令3
gnome-terminal --tab --title="TrackingAndU" --command="bash -c 'python python /home/eaibot/robocom_ws/src/tracking.py; $SHELL'"

