#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from geometry_msgs.msg import PoseWithCovarianceStamped,PoseStamped,Twist
from nav_msgs.msg import Odometry
from math import sqrt
import os
import time

global init_time

def set_initial_pose():
    rospy.init_node('set_initial_pose_node', anonymous=True)
    pub = rospy.Publisher('/initialpose', PoseWithCovarianceStamped, queue_size=10)
    rate = rospy.Rate(10)  # 10 Hz
    init_time = 0

    # Create and populate the PoseWithCovarianceStamped message
    pose_msg = PoseWithCovarianceStamped()
    pose_msg.header.frame_id = "map"  # Parent frame
    pose_msg.header.stamp = rospy.Time.now()

    pose_msg.pose.pose.position.x = 8.64159393311  # X position
    pose_msg.pose.pose.position.y = 3.70137190819  # Y position
    pose_msg.pose.pose.position.z = 0.0  # Z position

    pose_msg.pose.pose.orientation.x = 0.0
    pose_msg.pose.pose.orientation.y = 0.0
    pose_msg.pose.pose.orientation.z = -0.395337770686
    pose_msg.pose.pose.orientation.w = 0.918535816977  # Orientation (quaternion)

    # Covariance values (for position and orientation)
    pose_msg.pose.covariance = [0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06853892326654787]  # Adjust as needed

    while init_time <= 4 :
	pub.publish(pose_msg)
	rospy.loginfo("Published initial pose")
	init_time = init_time + 1
	rate.sleep()


def send_goal():
    global goal_count
    if goal_count == 0: #进入直角道
        # 创建第1个目标点消息
        goal_msg.header.seq = 0  # 设置目标点的序号
        goal_msg.header.stamp = rospy.Time.now()  # 设置目标点的时间戳
        goal_msg.header.frame_id = "map"  # 设置目标点参考的坐标系，一般是地图坐标系
        goal_msg.pose.position.x = 9.53165817261  # 设置目标点的 x 坐标
        goal_msg.pose.position.y = 1.96521031857  # 设置目标点的 y 坐标
        goal_msg.pose.position.z = 0.0  # 设置目标点的 z 坐标，一般设置为 0.0
        goal_msg.pose.orientation.x = 0.0  # 设置目标点的四元数 x 分量
        goal_msg.pose.orientation.y = 0.0  # 设置目标点的四元数 y 分量
        goal_msg.pose.orientation.z = -0.774542974259  # 设置目标点的四元数 z 分量
        goal_msg.pose.orientation.w = 0.63252128899  # 设置目标点的四元数 w 分量
    elif goal_count == 1: #过渡U型
        # 创建第2个目标点消息
        goal_msg.header.seq = 1  # 设置目标点的序号
        goal_msg.header.stamp = rospy.Time.now()  # 设置目标点的时间戳
        goal_msg.header.frame_id = "map"  # 设置目标点参考的坐标系，一般是地图坐标系
        goal_msg.pose.position.x = 8.92168235779  # 设置目标点的 x 坐标
        goal_msg.pose.position.y = 1.22006690502  # 设置目标点的 y 坐标
        goal_msg.pose.position.z = 0.0  # 设置目标点的 z 坐标，一般设置为 0.0
        goal_msg.pose.orientation.x = 0.0  # 设置目标点的四元数 x 分量
        goal_msg.pose.orientation.y = 0.0  # 设置目标点的四元数 y 分量
        goal_msg.pose.orientation.z = 0.940528310432  # 设置目标点的四元数 z 分量
        goal_msg.pose.orientation.w = -0.339715317988  # 设置目标点的四元数 w 分量
    elif goal_count == 2: #进入U型
        # 创建第3个目标点消息
        goal_msg.header.seq = 2  # 设置目标点的序号
        goal_msg.header.stamp = rospy.Time.now()  # 设置目标点的时间戳
        goal_msg.header.frame_id = "map"  # 设置目标点参考的坐标系，一般是地图坐标系
        goal_msg.pose.position.x = 7.70546865463  # 设置目标点的 x 坐标
        goal_msg.pose.position.y = 0.144097685814  # 设置目标点的 y 坐标
        goal_msg.pose.position.z = 0.0  # 设置目标点的 z 坐标，一般设置为 0.0
        goal_msg.pose.orientation.x = 0.0  # 设置目标点的四元数 x 分量
        goal_msg.pose.orientation.y = 0.0  # 设置目标点的四元数 y 分量
        goal_msg.pose.orientation.z = -0.762510490764  # 设置目标点的四元数 z 分量
        goal_msg.pose.orientation.w = 0.646975850766  # 设置目标点的四元数 w 分量
    elif goal_count == 3: #U型一半
        # 创建第4个目标点消息
        goal_msg.header.seq = 3  # 设置目标点的序号
        goal_msg.header.stamp = rospy.Time.now()  # 设置目标点的时间戳
        goal_msg.header.frame_id = "map"  # 设置目标点参考的坐标系，一般是地图坐标系
        goal_msg.pose.position.x = 7.82042837143  # 设置目标点的 x 坐标
        goal_msg.pose.position.y = -0.630423665047  # 设置目标点的 y 坐标
        goal_msg.pose.position.z = 0.0  # 设置目标点的 z 坐标，一般设置为 0.0
        goal_msg.pose.orientation.x = 0.0  # 设置目标点的四元数 x 分量
        goal_msg.pose.orientation.y = 0.0  # 设置目标点的四元数 y 分量
        goal_msg.pose.orientation.z = -0.452187997622  # 设置目标点的四元数 z 分量
        goal_msg.pose.orientation.w = 0.891922650686  # 设置目标点的四元数 w 分量
    elif goal_count == 4: #U型将出
        # 创建第5个目标点消息
        goal_msg.header.seq = 4  # 设置目标点的序号
        goal_msg.header.stamp = rospy.Time.now()  # 设置目标点的时间戳
        goal_msg.header.frame_id = "map"  # 设置目标点参考的坐标系，一般是地图坐标系
        goal_msg.pose.position.x = 8.72677993774  # 设置目标点的 x 坐标
        goal_msg.pose.position.y = -1.04409790039  # 设置目标点的 y 坐标
        goal_msg.pose.position.z = 0.0  # 设置目标点的 z 坐标，一般设置为 0.0
        goal_msg.pose.orientation.x = 0.0  # 设置目标点的四元数 x 分量
        goal_msg.pose.orientation.y = 0.0  # 设置目标点的四元数 y 分量
        goal_msg.pose.orientation.z = 0.227854433457  # 设置目标点的四元数 z 分量
        goal_msg.pose.orientation.w = 0.973695207523  # 设置目标点的四元数 w 分量
    elif goal_count == 5: #结束
        # 创建第6个目标点消息
        goal_msg.header.seq = 5  # 设置目标点的序号
        goal_msg.header.stamp = rospy.Time.now()  # 设置目标点的时间戳
        goal_msg.header.frame_id = "map"  # 设置目标点参考的坐标系，一般是地图坐标系
        goal_msg.pose.position.x = 10.9985866547  # 设置目标点的 x 坐标
        goal_msg.pose.position.y = 0.528826117516  # 设置目标点的 y 坐标
        goal_msg.pose.position.z = 0.0  # 设置目标点的 z 坐标，一般设置为 0.0
        goal_msg.pose.orientation.x = 0.0  # 设置目标点的四元数 x 分量
        goal_msg.pose.orientation.y = 0.0  # 设置目标点的四元数 y 分量
        goal_msg.pose.orientation.z = 0.373587733638 # 设置目标点的四元数 z 分量
        goal_msg.pose.orientation.w = 0.927594849746  # 设置目标点的四元数 w 分量
    elif goal_count == 6:  # 终结程序
        twist.linear.x = 0
	twist.angular.z = 0
	cmd_vel_pub.publish(twist)
	rospy.sleep(1)
	os._exit(0)
    # 发布目标点消息
    goal_publisher.publish(goal_msg)
    rospy.sleep(1)  # 延时以确保消息被发布
    rospy.loginfo("global goal count: %d", goal_count)  # 打印目标点的序号

def amcl_callback(amcl_pose_msg):
    global current_amcl_pose
    current_amcl_pose = amcl_pose_msg  # 更新全局变量

def odom_callback(odom_msg):
    global goal_count, current_amcl_pose
    send_goal()  # 发布目标点消息
    # 获取机器人当前位置
    current_position = current_amcl_pose.pose.pose.position
    current_orientation = current_amcl_pose.pose.pose.orientation
    # 计算机器人当前位置与目标点之间的欧几里得距离
    distance = sqrt((current_position.x - goal_msg.pose.position.x) ** 2 +
                    (current_position.y - goal_msg.pose.position.y) ** 2)
    angle_bias = sqrt((current_orientation.z - goal_msg.pose.orientation.z) ** 2 +
                      (current_orientation.w - goal_msg.pose.orientation.w) ** 2)
    rospy.loginfo("Distance to the goal: %f", distance)
    rospy.loginfo("Angle bias to the goal: %f", angle_bias)
    # 根据设定的阈值判断是否到达目标点
    if goal_count == 5 and distance < 1 and (angle_bias < 0.5 or angle_bias > 1.99):
        goal_count = goal_count + 1  # 目标点计数加1
        rospy.loginfo("Robot has reached the target point!")
    elif distance < 0.7 and (angle_bias < 0.4 or angle_bias > 1.99) and goal_count == 1:
	goal_count = goal_count + 1  # 目标点计数加1
        rospy.loginfo("Robot has reached the target point!")
    elif distance < 0.4 and (angle_bias < 0.3 or angle_bias > 1.99):  # 直角 
        goal_count = goal_count + 1  # 目标点计数加1
        rospy.loginfo("Robot has reached the target point!")
    # 到达目标点，停止机器人运动
    elif distance < 0.5 and (angle_bias < 0.3 or angle_bias > 1.99) and (goal_count >= 2 and goal_count <= 4): # U型
        goal_count = goal_count + 1  # 目标点计数加1
        rospy.loginfo("Robot has reached the target point!")
 	

if __name__ == '__main__':
    set_initial_pose() # 初始化初始位置
    goal_count = 0  # 目标点计数
    # 创建一个发布器，将目标点消息发送到 /move_base/goal 话题
    goal_publisher = rospy.Publisher('/move_base_simple/goal', PoseStamped, queue_size=10)
    cmd_vel_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)
    twist = Twist()
    # 等待1秒，确保发布者和订阅者之间的连接正常
    # 创建一个订阅器，订阅 /amcl_pose 话题，回调函数为 callback
    rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, amcl_callback, queue_size=1)
    rospy.Subscriber('/odom', Odometry, odom_callback, queue_size=1)
    # 创建一个目标点消息
    goal_msg = PoseStamped()
    # 循环等待回调函数
    rospy.spin()


