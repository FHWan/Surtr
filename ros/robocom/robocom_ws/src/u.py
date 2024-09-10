#!/usr/bin/env python
# coding=utf-8

import rospy
from sensor_msgs.msg import Image
import cv2, cv_bridge
import numpy
from geometry_msgs.msg import Twist
import time
from math import radians

#根据角度旋转，
def turnLeft(degree ,msg,pub):
    msg = Twist()
    angular_speed = radians(degree)  # 角速度为80度/秒
    relative_angle = radians(degree)  # 相对角度为80度

    # 设置线速度和角速度为零，停止小车
    msg.linear.x = 0
    msg.angular.z = 0
    
    # 发布消息，以确保小车停止运动
    pub.publish(msg)
    rospy.sleep(1)
    
    # 开始旋转
    msg.angular.z = angular_speed
    t0 = rospy.Time.now().to_sec()
    current_angle = 0

    while current_angle < relative_angle:
        pub.publish(msg)
        t1 = rospy.Time.now().to_sec()
        current_angle = angular_speed * (t1 - t0)

    # 停止旋转
    msg.angular.z = 0
    pub.publish(msg)
    rospy.sleep(1)

def turnRight(degree ,msg,pub):
    msg = Twist()
    angular_speed = radians(degree)  # 角速度为80度/秒
    relative_angle = radians(degree)  # 相对角度为80度

    # 设置线速度和角速度为零，停止小车
    msg.linear.x = 0
    msg.angular.z = 0
    
    # 发布消息，以确保小车停止运动
    pub.publish(msg)
    rospy.sleep(1)
    
    # 开始旋转
    msg.angular.z = -angular_speed
    t0 = rospy.Time.now().to_sec()
    current_angle = 0

    while current_angle < relative_angle:
        pub.publish(msg)
        t1 = rospy.Time.now().to_sec()
        current_angle = angular_speed * (t1 - t0)

    # 停止旋转
    msg.angular.z = 0
    pub.publish(msg)
    rospy.sleep(1)

def moveByTim(tim,msg,pub):
    msg.linear.x = 0.4  # 设置线速度为0.4m/s
    msg.angular.z = 0
    t0 = rospy.Time.now().to_sec() 
    current_time = 0

    while current_time < tim:  # 设置直行时间为4秒
        pub.publish(msg)
        t1 = rospy.Time.now().to_sec()
        current_time = t1 - t0



def draw_u():
    rospy.init_node('u_car_node',anonymous=True)

    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    msg = Twist()

    msg.linear.x = 0
    msg.angular.z = 0
    pub.publish(msg)
    rospy.sleep(1)


    #直到1
    moveByTim(4.5,msg,pub)

    #弯道1
    turnRight(45,msg,pub)

    moveByTim(1,msg,pub)

    turnRight(45,msg,pub)

    #直到2
    moveByTim(5,msg,pub)

    #U弯
    #1
    turnLeft(15,msg,pub)
    
    moveByTim(1.5,msg,pub)
    
    #2
    turnLeft(39,msg,pub)

    moveByTim(1.8,msg,pub)  

    #3
    turnLeft(35,msg,pub)
    
    moveByTim(1.2,msg,pub)  
    
    #4
    turnLeft(30,msg,pub)

    moveByTim(1,msg,pub)

    #5
    turnLeft(45,msg,pub)

    moveByTim(1.2,msg,pub)

    #6
    turnLeft(15,msg,pub)

    moveByTim(3,msg,pub)

    #7
    turnLeft(5,msg,pub)

    moveByTim(4,msg,pub)




  
    #最终停止
    msg.linear.x  = 0.0
    pub.publish(msg)    

if __name__=='__main__':
        try:
             draw_u()
        except rospy.ROSInternalException:
             pass