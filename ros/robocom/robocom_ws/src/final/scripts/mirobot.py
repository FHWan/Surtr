#!/usr/bin/env python
# -*- coding: UTF-8 -*-
#根据数据类型import，记得加.msg

import transforms3d as tfs
import time
import tf
from geometry_msgs.msg import TransformStamped
import tf2_ros.transform_broadcaster
import math   
import rospy, sys
import moveit_commander
from moveit_msgs.msg import RobotTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from sensor_msgs.msg import Image
import numpy as np
from geometry_msgs.msg import PoseStamped, Pose
from std_msgs.msg import String
from tf.transformations import euler_from_quaternion, quaternion_from_euler
from sensor_msgs.msg import Image
from cv_bridge import CvBridge,CvBridgeError
import cv2
from mirobot_urdf_2.srv import *
import os

if __name__ =='__main__':
    rospy.init_node("pointcloud_tf")
    rate = rospy.Rate(10.0)

    moveit_commander.roscpp_initialize(sys.argv)
    arm = moveit_commander.MoveGroupCommander('manipulator')
    pump_s=rospy.ServiceProxy("switch_pump_status",mirobotPump)
    arm.set_pose_reference_frame('base')
    joint_position=[-1.5,0,0.8,0,-2.5,-1]
    arm.set_joint_value_target(joint_position)
    arm.go(wait=True)

    listener = tf.TransformListener()
    get_pose = False
    posestamped=PoseStamped()

    posestamped.header.frame_id = 'camera_rgb_optical_frame'
   
    now = rospy.Time.now()
    listener.waitForTransform("camera_rgb_optical_frame", "tag_3", now, rospy.Duration(10))
    (trans_1, rot) = listener.lookupTransform("camera_rgb_optical_frame", "tag_3", now)

    now = rospy.Time.now()
    listener.waitForTransform("camera_rgb_optical_frame", "tag_0", now, rospy.Duration(10))
    (trans_2, rot) = listener.lookupTransform("camera_rgb_optical_frame", "tag_0", now)

    now = rospy.Time.now()
    listener.waitForTransform("camera_rgb_optical_frame", "tag_5", now, rospy.Duration(10))
    (trans_no, rot) = listener.lookupTransform("camera_rgb_optical_frame", "tag_5", now)

    positions = {'trans_1': trans_1, 'trans_2': trans_2, 'trans_no': trans_no}
    
    # 对字典按值进行排序
    sorted_positions = sorted(positions.items(), key=lambda x: x[1])
    
    # 获取排序后的键
    sorted_keys = [item[0] for item in sorted_positions]
    
    # 输出每个变量的位置
    for key in sorted_keys:
        if key == sorted_keys[0]:
            position = '左边'
        elif key == sorted_keys[1]:
            position = '中间'
        else:
            position = '右边'
        if key != 'trans_no':
            print("要抓取的物料位置: {}".format(position))

    os._exit(0)

