#!/usr/bin/env python2
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
    #joint_position=[0,0,0,0,0,0]
    #arm.set_joint_value_target(joint_position)
    #arm.go(wait=True)
    joint_position=[-0.32,0.15,0.6,0,-2.25,0]  #一动
    arm.set_joint_value_target(joint_position)
    arm.go(wait=True)
    time.sleep(1)
    joint_position=[-0.2,0.8,-0.1,0,-2.1,-1.5]
    arm.set_joint_value_target(joint_position)
    arm.go(wait=True)
    time.sleep(1)
    pump_s(True)
    joint_position=[-0.1,1.2,-0.8,0,-1.9,-1.5]
    arm.set_joint_value_target(joint_position)
    arm.go(wait=True)
    
    time.sleep(30)
    pump_s(False)
    os._exit(0)

    listener = tf.TransformListener()
    get_pose = False
    posestamped=PoseStamped()

    posestamped.header.frame_id = 'camera_rgb_optical_frame'
   
    now = rospy.Time.now()
    listener.waitForTransform("camera_rgb_optical_frame", "tag_2", now, rospy.Duration(1.5))
    (trans, rot) = listener.lookupTransform("camera_rgb_optical_frame", "tag_2", now)
    print(trans[0], trans[1], trans[2], rot[0], rot[1], rot[2], rot[3])
    posestamped.pose.position.x=trans[0]
    posestamped.pose.position.y=trans[1]
    posestamped.pose.position.z=trans[2]
    posestamped.pose.orientation.x=rot[0]
    posestamped.pose.orientation.y=rot[1]
    posestamped.pose.orientation.z=rot[2]
    posestamped.pose.orientation.w=rot[3]
    m1=tfs.euler.euler2mat(math.radians(180),math.radians(0),math.radians(0))
    m2=tfs.quaternions.quat2mat([rot[3],rot[0],rot[1],rot[2]])
    rot2=tfs.quaternions.mat2quat(np.dot(m2,m1)[0:3,0:3])

    m2=tf.TransformBroadcaster()
    t2 = TransformStamped()
    t2.header.frame_id = 'camera_rgb_optical_frame'
    t2.header.stamp = rospy.Time(0)
    t2.child_frame_id = 't2'
    t2.transform.translation = posestamped.pose.position
    t2.transform.rotation.w=rot2[0]
    t2.transform.rotation.x=rot2[1]
    t2.transform.rotation.y=rot2[2]
    t2.transform.rotation.z=rot2[3]
    t2.transform.rotation=posestamped.pose.orientation
    #posestamped.pose.orientation=t2.transform.rotation
    rate = rospy.Rate(1)
    m2.sendTransformMessage(t2)

    now = rospy.Time.now()
    listener.waitForTransform("/base", "/camera_rgb_optical_frame", now, rospy.Duration(2.0))
    pose_stamped_return = listener.transformPose("/base", posestamped)
    print pose_stamped_return
    m2.sendTransformMessage(t2)


    print("OK_2")
    rospy.wait_for_service("switch_pump_status")
    pump_s=rospy.ServiceProxy("switch_pump_status",mirobotPump)
    pump_s(True)
    #joint_position=[0,0,0,0,0,0]
    joint_position=[0.32,0.17,-0.31,-0.33,-0.017,-0.07]
    arm.set_joint_value_target(joint_position)
    arm.go(wait=True)
    pump_s(False)

    rate.sleep()





