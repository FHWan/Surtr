import socket, os, struct
import face_recognition
import sys
sys.path.append('/home/pi/Downloads/opencv-3.4.0/build/lib/python3')
import cv2
import numpy as np
import os
import serial
import time

"""设置 ip 地址"""
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(('x.x.x.x', 8000))#自己服务器的IP

ser = serial.Serial('/dev/ttyUSB0', 115200)  # 设置端口和波特率
#ser = serial.Serial('/dev/ttyAMA0', 115200)  # 设置端口和波特率
if ser.isOpen == False:  # 检查串口是否打开
    ser.open()                # 打开串口
ser.write(b"Raspberry pi is ready")

# This is a demo of running face recognition on live video from your webcam. It's a little more complicated than the
# other example, but it includes some basic performance tweaks to make things run a lot faster:
#   1. Process each video frame at 1/4 resolution (though still display it at full resolution)
#   2. Only detect faces in every other frame of video.
 
# PLEASE NOTE: This example requires OpenCV (the `cv2` library) to be installed only to read from your webcam.
# OpenCV is *not* required to use the face_recognition library. It's only required if you want to run this
# specific demo. If you have trouble installing it, try any of the other demos that don't require it instead.
 
# Get a reference to webcam #0 (the default one)
video_capture = cv2.VideoCapture(0)

xzf_image = face_recognition.load_image_file("/home/pi/faceuse/aeduse/admin_faces/xzf.jpg")
xzf_face_encoding = face_recognition.face_encodings(xzf_image)[0]

fan_image = face_recognition.load_image_file("/home/pi/faceuse/aeduse/admin_faces/fan.jpg")
fan_face_encoding = face_recognition.face_encodings(fan_image)[0]

# wqz_image = face_recognition.load_image_file("/home/pi/faceuse/aeduse/admin_faces/wqz.jpg")
# wqz_face_encoding = face_recognition.face_encodings(wqz_image)[0]
 
# Create arrays of known face encodings and their names
known_face_encodings = [
    xzf_face_encoding,
    fan_face_encoding,
#     wqz_face_encoding
]
known_face_names = [
    "xzf",
    "fan",
#     "wqz",
    "Unknown"
]
max_value = 0
max_index = 0

face_time = [
    0,
    0,
    0
]

# Initialize some variables
face_locations = []
face_encodings = []
face_names = []
process_this_frame = True
process_use = False
response = "NULL"
time_count = 0
get_count = 0
identity = "unknown"
threshold = 0.5
    
while True:
    # Grab a single frame of video
    ret, frame = video_capture.read()
    
    # Resize frame of video to 1/4 size for faster face recognition processing
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
 
    # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
    rgb_small_frame = small_frame[:, :, ::-1]
    
    size = ser.inWaiting()               # 获得缓冲区字符
    if size != 0:
        response = ser.read(size)
        print(response)
        ser.flushInput()                 # 清空接收缓存区
 
    if response == b'OK\r\n':
        time_count = 0
        get_count = 0
        response = "NULL"
        process_use = True
        
    if process_use == True:
         
        time_count=time_count+1
        if time_count >= 40:
            time_count = 0
            get_count = 0
            process_use = False
            print("timeout\r\n")
            
        # Only process every other frame of video to save time
        if process_this_frame:
            # Find all the faces and face encodings in the current frame of video
            face_locations = face_recognition.face_locations(rgb_small_frame)
            face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)
     
            face_names = []
            for face_encoding in face_encodings:
                # See if the face is a match for the known face(s)
                matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
                name = "Unknown"
                
                # # If a match was found in known_face_encodings, just use the first one.
                # if True in matches:
                #     first_match_index = matches.index(True)
                #     name = known_face_names[first_match_index]
     
                # Or instead, use the known face with the smallest distance to the new face
                face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
                if np.min(face_distances) <= threshold:
                    best_match_index = np.argmin(face_distances)
                    if matches[best_match_index]:
                        name = known_face_names[best_match_index]
                 
                face_names.append(name)
     
        process_this_frame = not process_this_frame
         
        # Display the results
        for (top, right, bottom, left), name in zip(face_locations, face_names):
            # Scale back up face locations since the frame we detected in was scaled to 1/4 size
            top *= 4
            right *= 4
            bottom *= 4
            left *= 4
      
            get_count = get_count+1
            time_count = 0
      
            if   name =="Unknown":
                face_time[2] = face_time[2]+1
            elif name =="xzf":
                face_time[0] = face_time[0]+1
            elif name =="fan":
                face_time[1] = face_time[1]+1
#             elif name =="wqz":
#                 face_time[2] = face_time[2]+1
            
            if get_count >= 5:
                print("0,",face_time[0])
                print("1,",face_time[1])
                print("2,",face_time[2])
#                 print("3,",face_time[3])
                max_value = max(face_time)
                print("max_value",max_value)
                max_index = face_time.index(max_value)
                print("index",max_index)
                if max_value <= 3:
                    name = "Unknown"
                else:
                    name = known_face_names[max_index]
                face_time = [0 for _ in face_time]
                
                if name == "Unknown":
                    identity = "unknown"
                else:
                    identity = "admin"
                print("last",name)
                # 生成文件路径
                image_path = "/home/pi/faceuse/aeduse/{}_use/{}_face_{}.jpg".format(identity,name,int(time.time()))
                # 确保保存路径存在
                os.makedirs("/home/pi/faceuse/aeduse/{}_use/".format(identity), exist_ok=True)
                # 截取人脸区域
                # 保存人脸图片
                cv2.imwrite(image_path, frame[top:bottom, left:right])
                
                filepath = image_path
                
                ser.write(os.path.basename(filepath).encode())
                ser.write(os.path.basename(filepath).encode())
                ser.write(os.path.basename(filepath).encode())
                ser.write(b"\r\n")
                
                if os.path.isfile(filepath):
                    fileinfo_size = struct.calcsize('128sq')  # 定义打包规则
                    # 定义文件头信息，包含文件名和文件大小
                    fhead = struct.pack('128sq',bytes(os.path.basename(filepath),encoding='utf-8'), os.stat(filepath).st_size)
                    s.send(fhead)
                    print('client filepath: ', os.path.basename(filepath), os.stat(filepath).st_size)

                    fo = open(filepath, 'rb')
                    while True:
                        filedata = fo.read(1024)
                        if not filedata:
                            break
                        s.send(filedata)
                    #time.sleep(0.5)
                    fo.close()
            
            # Draw a box around the face
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
     
            # Draw a label with a name below the face
            cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            font = cv2.FONT_HERSHEY_DUPLEX
            cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
            
            if get_count >= 5:
                time_count = 0
                get_count = 0
                process_use = False
                print("getover\r\n")
                break
    # Display the resulting image
    cv2.resizeWindow('Video', 1024, 600)
    
    resized_frame = cv2.resize(frame, (1024, 600))
    
    cv2.imshow('Video', resized_frame)
    
    cv2.moveWindow('Video', -2, -30)
    
    # Hit 'q' on the keyboard to quit!
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
# Release handle to the webcam
video_capture.release()
cv2.destroyAllWindows()