#!/usr/bin/env python
# coding=utf-8

import rospy
from sensor_msgs.msg import Image
import cv2
import cv_bridge
from geometry_msgs.msg import Twist
import time
from std_msgs.msg import String
import os


class Pic_foll:
    def __init__(self):
        self.bridge = cv_bridge.CvBridge()
        self.image_sub = rospy.Subscriber("/camera/rgb/image_raw", Image, self.image_deep_callback)
        self.cmd_vel_pub = rospy.Publisher("cmd_vel", Twist, queue_size=1)
        self.cam_sub = rospy.Subscriber("chatter", String, self.doMsg)
        self.twist = Twist()
        
        self.cam_time = "0"
        self.sign_1 = False
        self.sign_2 = False
        self.sign_3 = False
        
        self.counter = 1
        self.max_images = 8
        self.save_path_1 = "/home/eaibot/2024final/hz/24pic"
        self.save_path_2 = "/home/eaibot/2024final/rq/24pic"
        # save image 1ms
        self.pic_time = 0
        self.save_timer = rospy.Timer(rospy.Duration(1), self.save_image_callback)

    def doMsg(self, msg):
        self.cam_time = msg.data

    def image_deep_callback(self, msg):
    
        try:
            # ROS to OpenCV
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            
            # 处理图像
            self.processed_image = cv_image
            
        # 检查 tracking2024 模块中的状态
        
            if self.cam_time == "1" and self.sign_1 == False:
                self.save_image('processed01.jpg')
                self.sign_1 = True
            elif self.cam_time == "2" and self.sign_2 == False:
                self.save_image('processed02.jpg')
                self.sign_2 = True
            elif self.cam_time == "3" and self.sign_3 == False:
                self.save_image('processed03.jpg')
                time.sleep(3)
                os._exit(0)

        except cv_bridge.CvBridgeError as e:
            rospy.logerr("Error converting ROS image message: %s", e)

    def save_image(self, filename):
        if self.cam_time == "1" or self.cam_time == "3":
            filepath = "{}/{}".format(self.save_path_1, filename)
        elif self.cam_time == "2":
            filepath = "{}/{}".format(self.save_path_2, filename)

        if hasattr(self, 'processed_image'):
            cv2.imwrite(filepath, self.processed_image)
            rospy.loginfo("Saved processed image: {}".format(filepath))

    def save_image_callback(self, event):
        # 这里可以继续处理定时保存图像的逻辑
        pass
    
    
if __name__ == '__main__':
    rospy.init_node('pic_foll')
    pic_foll = Pic_foll()
    print("OK")
    rospy.spin()
