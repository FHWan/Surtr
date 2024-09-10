#!/usr/bin/env python2
# coding=utf-8

import rospy
from sensor_msgs.msg import Image
import cv2, cv_bridge
import numpy
from geometry_msgs.msg import Twist
from std_msgs.msg import String
import time
import os

global picture_1, picture_2, picture_3
global pic_time,T1
pic_time = 0
picture_1 = False
picture_2 = False
picture_3 = False


class Follower:
    def __init__(self):

        self.bridge = cv_bridge.CvBridge()
        self.image_sub = rospy.Subscriber("/usb_cam/image_raw", Image, self.image_callback)
        self.cmd_vel_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)
        self.cam_pub = rospy.Publisher("chatter", String, queue_size=10)
        self.twist = Twist()

        self.cam_msg = String()  # 创建 msg 对象
        self.cam_msg.data = "0"
        # PID参数定义
        self.Kp = 0.02
        self.Ki = 0.0
        self.Kd = 0.0
        self.num = 0
        self.data = 0.0
        self.data1 = 0.0
        self.nav_init = False  # 将 nav_init 设为类属性

        self.PIDOutput = 0.0  # PID控制器输出

        self.Error = 0.0
        self.LastError = 0.0
        self.LastLastError = 0.0

        # 红绿线检测
        self.AREA_THRESHOLD = 100000  # 你可以根据需要调整这个阈值
        self.red_detected = False

    def image_callback(self, msg):
        global picture_1, picture_2, picture_3
        global pic_time,T1

        image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

	if self.nav_init == True:
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
        # print("red:",self.red_detected)
        ##############################################

        lower_black = numpy.array([0, 0, 0])
        upper_black = numpy.array([85, 85, 85])
        mask = cv2.inRange(hsv, lower_black, upper_black)
        masked = cv2.bitwise_and(image, image, mask=mask)

        # 在图像某处绘制一个指示，因为只考虑20行宽的图像，所以使用numpy切片将以外的空间区域清空
        h, w, d = image.shape
        search_top = 1 * h / 2
        search_bot = search_top + 15
        mask[0:search_top, 0:w] = 0
        mask[search_bot:h, 0:w] = 0
        # 计算mask图像的重心，即几何中心
        M = cv2.moments(mask)
        T2 = time.time()
        T3 = T2 - T1
        print("time:", T3)

        # 拍照标志位
        if self.nav_init == False:
            if self.cam_msg.data == "0" and T3 >= 20:   #第一个大厦
                self.cam_msg.data = "1"
            elif self.cam_msg.data == "1" and T3 >= 45: #人群
                self.cam_msg.data = "2"
        else:
            if self.cam_msg.data == "2" and T3 >= 13: #第二个大厦
                self.cam_msg.data = "3"
        self.cam_pub.publish(self.cam_msg)

        # 停车
        if self.nav_init == True and T3 > 12 and self.red_detected == True:
	    T1 = time.time()
            while T2-T1 < 1.8:
		T2 = time.time()
		self.twist.linear.x = 0.3
                self.twist.angular.z = 0
        	self.cmd_vel_pub.publish(self.twist)
	    self.twist.linear.x = 0
	    self.twist.angular.z = 0
	    self.cmd_vel_pub.publish(self.twist)
	    time.sleep(1)
	    os._exit(0)

        if M['m00'] > 0:
            cx = int(M['m10'] / M['m00'])
            cy = int(M['m01'] / M['m00'])
            cv2.circle(image, (cx, cy), 20, (0, 0, 255), -1)
            self.LastLastError = self.LastError
            self.LastError = self.Error
            self.Error = w / 2 - cx
            # 计算增量
            IncrementalValue = self.Kp * (self.Error - self.LastError) + self.Ki * self.Error + self.Kd * (
                        self.Error - 2 * self.LastError + self.LastLastError)
            # 计算输出
            self.PIDOutput += IncrementalValue
            if self.nav_init == True:
                self.twist.linear.x = 0.15
            else:
                self.twist.linear.x = 0.28
            self.twist.angular.z = float(self.PIDOutput) / 8
            if self.nav_init == True:
                self.twist.angular.z = self.twist.angular.z / 2
        else:
            if T3 > 46 and self.nav_init == False:
                self.twist.linear.x = 0
                self.twist.angular.z = -0.5
                self.cmd_vel_pub.publish(self.twist)
                time.sleep(2)
                self.twist.angular.z = 0
                self.cmd_vel_pub.publish(self.twist)

                os.system('python robocom_ws/src/final/scripts/nav_demo.py')
		#os._exit(0)
                self.nav_init = True
                print("OK")
                T1 = time.time()    #刷新时间
                self.twist.linear.x = 0
                self.twist.angular.z = 0
                self.cmd_vel_pub.publish(self.twist)

            else:
		#if self.nav_init == True and T3 < 6.5:
		#    self.twist.linear.x = 0.2
                #    self.twist.angular.z = 0.4
		if self.nav_init == True and T3 >= 14:
		    self.twist.linear.x = 0.4
                    self.twist.angular.z = 0
		elif self.nav_init == True and T3 < 14:
		    self.twist.linear.x = 0.17
                    self.twist.angular.z = 0
		else:               
		    self.twist.linear.x = 0.3
                    self.twist.angular.z = 0
		#self.twist.linear.x = 0.3
		#self.twist.angular.z = 0
        self.cmd_vel_pub.publish(self.twist)


rospy.init_node("opencv")
T1 = time.time()
follower = Follower()
rospy.spin()

