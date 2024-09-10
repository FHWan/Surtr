#!/usr/bin/env python
# coding=utf-8

import rospy
from std_msgs.msg import String
import subprocess
import multiprocessing
import time

class DynamicLauncher:
    def __init__(self):
        # 初始化 ROS 节点
        rospy.init_node('dynamic_launcher')

        # 订阅主题 "chatter"
        self.subscriber = rospy.Subscriber("chatter", String, self.callback)

        # 定义脚本对应的映射
        self.script_map = {
            "1": 'hz.py',
            "2": '/home/eaibot/2024final/rq/rq.py',
            "3": 'hz.py'
        }

        # 存储进程
        self.processes = []
        self.sign_1 = False
        self.sign_2 = False
        self.sign_3 = False

    def callback(self, msg):
        if msg.data == "1" and self.sign_1 == False:
            print("火灾_1开始识别")
            script = self.script_map.get(msg.data)
            self.start_script(script)
            self.sign_1 = True
        elif msg.data == "2" and self.sign_2 == False:
            print("人群开始识别")
            script = self.script_map.get(msg.data)
            self.start_script(script)
            self.sign_2 = True
      #  elif msg.data == "3" and self.sign_3 == False:
      #      print("火灾_2开始识别")
      #      script = self.script_map.get(msg.data)
      #      self.start_script(script)
      #      self.sign_3 = True

    def start_script(self, script):
        # 定义运行脚本的目标函数
        def run_script(script):
            subprocess.run(['python', script])

        # 创建并启动进程
        process = multiprocessing.Process(target=run_script, args=(script,))
        self.processes.append(process)
        process.start()

    def run(self):
        # 保持节点运行
        rospy.spin()


if __name__ == '__main__':
    launcher = DynamicLauncher()
    print("OK")
    launcher.run()

