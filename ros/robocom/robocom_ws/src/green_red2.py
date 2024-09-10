#!/usr/bin/env python
# coding=utf-8
from tracking_gr import Follower  # 这里替换成实际文件名
def print_green_red_status():
    follower = Follower()  # 实例化Follower类
    # 假设已经触发了image_callback方法，这里直接打印变量值
    print("Green detected:", follower.self.green_detected)
    print("Red counter:", follower.self.red_counter)

if __name__ == "__main__":
    print_green_red_status()
