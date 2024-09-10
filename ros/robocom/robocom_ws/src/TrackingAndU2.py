#!/usr/bin/env python
# coding=utf-8

import rospy
from sensor_msgs.msg import Image
import cv2, cv_bridge
import numpy
from geometry_msgs.msg import Twist
import time
from math import radians

#���ݽǶ���ת��
def turnLeft(degree ,msg,pub):
    msg = Twist()
    angular_speed = radians(degree)  # ���ٶ�Ϊ80��/��
    relative_angle = radians(degree)  # ��ԽǶ�Ϊ80��

    # �������ٶȺͽ��ٶ�Ϊ�㣬ֹͣС��
    msg.linear.x = 0
    msg.angular.z = 0
    
    # ������Ϣ����ȷ��С��ֹͣ�˶�
    pub.publish(msg)
    rospy.sleep(1)
    
    # ��ʼ��ת
    msg.angular.z = angular_speed
    t0 = rospy.Time.now().to_sec()
    current_angle = 0

    while current_angle < relative_angle:
        pub.publish(msg)
        t1 = rospy.Time.now().to_sec()
        current_angle = angular_speed * (t1 - t0)

    # ֹͣ��ת
    msg.angular.z = 0
    pub.publish(msg)
    rospy.sleep(1)

def turnRight(degree ,msg,pub):
    msg = Twist()
    angular_speed = radians(degree)  # ���ٶ�Ϊ80��/��
    relative_angle = radians(degree)  # ��ԽǶ�Ϊ80��

    # �������ٶȺͽ��ٶ�Ϊ�㣬ֹͣС��
    msg.linear.x = 0
    msg.angular.z = 0
    
    # ������Ϣ����ȷ��С��ֹͣ�˶�
    pub.publish(msg)
    rospy.sleep(1)
    
    # ��ʼ��ת
    msg.angular.z = -angular_speed
    t0 = rospy.Time.now().to_sec()
    current_angle = 0

    while current_angle < relative_angle:
        pub.publish(msg)
        t1 = rospy.Time.now().to_sec()
        current_angle = angular_speed * (t1 - t0)

    # ֹͣ��ת
    msg.angular.z = 0
    pub.publish(msg)
    rospy.sleep(1)

def moveByTim(tim,msg,pub):
    msg.linear.x = 0.4  # �������ٶ�Ϊ0.4m/s
    msg.angular.z = 0
    t0 = rospy.Time.now().to_sec() 
    current_time = 0

    while current_time < tim:  # ����ֱ��ʱ��Ϊ4��
        pub.publish(msg)
        t1 = rospy.Time.now().to_sec()
        current_time = t1 - t0

def draw_u(msg,pub):
    
    msg.linear.x = 0
    msg.angular.z = 0
    pub.publish(msg)
    rospy.sleep(1)


    #ֱ��1
    moveByTim(4.5,msg,pub)

    #���1
    turnRight(45,msg,pub)

    moveByTim(1,msg,pub)

    turnRight(45,msg,pub)

    #ֱ��2
    moveByTim(5,msg,pub)

    #U��
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
    turnLeft(10,msg,pub)

    moveByTim(3.5,msg,pub)




  
    #����ֹͣ
    msg.linear.x  = 0.0
    pub.publish(msg)    

cnt = 0
tack = 0
switch = True
switchU = False
tmp = True
tt = 0
class Follower:
    def __init__(self):
        self.bridge = cv_bridge.CvBridge()
        self.image_sub = rospy.Subscriber("/usb_cam/image_raw", Image, self.image_callback)
        self.cmd_vel_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)
        self.twist = Twist()

        #PID��������
        self.Kp = 0.02
        self.Ki = 0.0
        self.Kd = 0.0
        self.num = 0
        self.data = 0.0
        self.data1 = 0.0

        self.PIDOutput =0.0         #PID���������

        self.Error = 0.0
        self.LastError = 0.0
        self.LastLastError = 0.0

    def image_callback(self, msg):
        global switch
        global cnt
        global tack
        global switchU
        global tmp
        global tt
        global call
        image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        lower_black = numpy.array([0, 0, 0])
        upper_black = numpy.array([85, 85, 85])
        mask = cv2.inRange(hsv, lower_black, upper_black)
        masked = cv2.bitwise_and(image, image, mask=mask)

        # ��ͼ��ĳ������һ��ָʾ����Ϊֻ����20�п���ͼ������ʹ��numpy��Ƭ������Ŀռ��������
        h, w, d = image.shape
        search_top = 1*h/2
        search_bot = search_top + 15
        mask[0:search_top, 0:w] = 0
        mask[search_bot:h, 0:w] = 0
        # ����maskͼ������ģ�����������
        M = cv2.moments(mask)
        print("M��ֵ:",M)
        if M['m00'] > 0:
            #Ѱ�߶�ջ
            if tack > 0:
                tack= tack -1
            if cnt >= 0:
                cnt = cnt + 1
            
            
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            cv2.circle(image, (cx, cy), 20, (0, 0, 255), -1)
            self.LastLastError = self.LastError
            self.LastError = self.Error
            #erro = cx - w/2
            self.Error = w/2 - cx
            #��������
            IncrementalValue = self.Kp*(self.Error - self.LastError) + self.Ki * self.Error +self.Kd *(self.Error -2*self.LastError +self.LastLastError)
            #�������
            self.PIDOutput += IncrementalValue
           
            self.twist.linear.x = 0.22
            self.twist.angular.z = float(self.PIDOutput)/8
            self.cmd_vel_pub.publish(self.twist)
           
        else:
            #���жϴ���U���׼���׶� ���ڼ�ʹ����U����հ״���
            if cnt >= 1400 and tmp == True:
                tmp = False
                return
            #��һ�ι��ź���ù��ţ�U���������׼�� �����߼�ֻ��ִ��һ��
            if tack >= 31:
                tt = tt  + 1
                if tt <= 1:            
                    switch = False
                    switchU = True
                return
            

            #���ź�����tack �϶ѣ�����û�����ƣ�ֻҪswitch��
            if switch:
                if M['m00'] <= 0:
                    if M['m00'] <= 0:            
                        print("������...")
                        print("switch =",switch)
                        tack = tack + 1
                        self.twist.linear.x = 0.51
                        self.twist.angular.z = 0
                        self.cmd_vel_pub.publish(self.twist)
                        return 
                                                  
           
            

                      
            #���ź����Ѿ����ã�����U���׼��
            if switchU:
                #U���֮ǰ��ջ
                tack = tack + 1
                if tmp:
                    #˫����֮�����֮ǰ�Ŀհ״���
                    self.twist.linear.x = 0.45
                    self.twist.angular.z = 0
                    self.cmd_vel_pub.publish(self.twist)
                    return
                print("��ʼ����...")
                print("switchU = ",switchU)
                try:
                    self.twist.linear.x = 0
                    self.twist.angular.z = 0
                    self.cmd_vel_pub.publish(self.twist)
                    #U����Ƕ�׼��
                    turnRight(12.5,self.twist,self.cmd_vel_pub)

                    self.twist.linear.x = 0
                    self.twist.angular.z = 0
                    self.cmd_vel_pub.publish(self.twist)
                    #U���ִ��
                    draw_u(self.twist,self.cmd_vel_pub)
                    #U���׼���رգ����ź�������
                    switchU = False
                    switch = True
                    #���׽�����ֵ�㷨
                    tt = 100
                    #��ջ�س�ʼ��
                    cnt = 0
                    tack = 0
                except rospy.ROSInternalException:
                    pass
                return
            
        print("tack = ",tack)
        print("switch =",switch)
        print("switchU = ",switchU)    
        print("tmp = ",tmp,"cnt",cnt)
       


rospy.init_node("opencv")
follower = Follower()
rospy.spin()