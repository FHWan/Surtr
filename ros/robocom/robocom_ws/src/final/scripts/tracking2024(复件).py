#!/usr/bin/env python
# coding=utf-8

import rospy
from sensor_msgs.msg import Image
import cv2, cv_bridge
import numpy
from geometry_msgs.msg import Twist
import time
import os

global picture_1,picture_2,picture_3

picture_1 = False
picture_2 = False
picture_3 = False

class Follower:
    def __init__(self):
        self.bridge = cv_bridge.CvBridge()
        self.image_sub = rospy.Subscriber("/usb_cam/image_raw", Image, self.image_callback)
        self.cmd_vel_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)
        self.twist = Twist()

        #PID参数定义
        self.Kp = 0.02
        self.Ki = 0.0
        self.Kd = 0.0
        self.num = 0
        self.data = 0.0
        self.data1 = 0.0
	self.nav_init = False  # 将 nav_init 设为类属性

        self.PIDOutput =0.0         #PID控制器输出

        self.Error = 0.0
        self.LastError = 0.0
        self.LastLastError = 0.0

	# 红绿线检测
        self.AREA_THRESHOLD = 100000  # 你可以根据需要调整这个阈值
        self.red_detected = False

    def image_callback(self, msg):
	global picture_1,picture_2,picture_3

        image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

########### 定义红色的HSV范围 #################
        lower_red1 = numpy.array([0, 100, 100])
        upper_red1 = numpy.array([10, 255, 255])
        lower_red2 = numpy.array([160, 100, 100])
        upper_red2 = numpy.array([180, 255, 255])

        # 创建红色的掩膜
        red_mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
        red_mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
        red_mask = red_mask1 + red_mask2

        # 查找红色区域的轮廓
        red_contours, _ = cv2.findContours(red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        red_area = sum(cv2.contourArea(c) for c in red_contours)

        if red_area <= self.AREA_THRESHOLD:
            self.red_detected = False
        else:
            self.red_detected = True
	#print("red:",self.red_detected)
##############################################

        lower_black = numpy.array([0, 0, 0])
        upper_black = numpy.array([85, 85, 85])
        mask = cv2.inRange(hsv, lower_black, upper_black)
        masked = cv2.bitwise_and(image, image, mask=mask)

        # 在图像某处绘制一个指示，因为只考虑20行宽的图像，所以使用numpy切片将以外的空间区域清空
        h, w, d = image.shape
        search_top = 1*h/2
        search_bot = search_top + 15
        mask[0:search_top, 0:w] = 0
        mask[search_bot:h, 0:w] = 0
        # 计算mask图像的重心，即几何中心
        M = cv2.moments(mask)
        T2 = time.time()
	T3 = T2 - T1
        print("time:", T3)
	
	#拍照标志位
	if picture_1 == False and T3>=20:
	    picture_1 = True
	elif picture_2 == False and T3>=44:
	    picture_2 = True
	elif picture_3 == False and T3>=110:
	    picture_3 = True
	print("pic_1:", picture_1,"pic_2:",picture_2,"pic_3:",picture_3)
	#停车
	if T3>120 and self.red_detected == True:
	    while True:
		self.twist.linear.x = 0
	        self.twist.angular.z = 0
       		self.cmd_vel_pub.publish(self.twist)

        if M['m00'] > 0:
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            cv2.circle(image, (cx, cy), 20, (0, 0, 255), -1)
            self.LastLastError = self.LastError
            self.LastError = self.Error
            self.Error = w/2 - cx
            #计算增量
            IncrementalValue = self.Kp*(self.Error - self.LastError) + self.Ki * self.Error +self.Kd *(self.Error -2*self.LastError +self.LastLastError)
            #计算输出
            self.PIDOutput += IncrementalValue
            self.twist.linear.x = 0.28
            self.twist.angular.z = float(self.PIDOutput)/8
        else:
	    if T3>44 and self.nav_init == False:
		self.twist.linear.x = 0
	        self.twist.angular.z = -0.5
       		self.cmd_vel_pub.publish(self.twist)
		time.sleep(5)
		self.twist.angular.z = 0
       	    	self.cmd_vel_pub.publish(self.twist)

	        os.system('python robocom_ws/src/final/scripts/nav_demo.py')
		self.nav_init = True
		print("OK")
		self.twist.linear.x = 0
	        self.twist.angular.z = 0
       		self.cmd_vel_pub.publish(self.twist)
			
  	    else:
	        self.twist.linear.x = 0.3
	        self.twist.angular.z = 0
        self.cmd_vel_pub.publish(self.twist)


rospy.init_node("opencv")
T1 = time.time()
follower = Follower()
rospy.spin()

