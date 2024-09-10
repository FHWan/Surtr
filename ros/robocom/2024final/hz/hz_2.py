# -*- coding: UTF-8 -*-
import time
import cv2
import detect_with_API
import torch
import os
import logging
import re
from paddleocr import PaddleOCR
logging.getLogger("ppocr").setLevel(logging.WARNING)

ocr = PaddleOCR(
    use_angle_cls=True,  # 是否使用文字方向分类器
    lang="ch",  # 语言设置为中文
    use_gpu=False,  # 不使用GPU
    rec_model_dir=r'PaddleOCR/inference/ch_PP-OCRv3_rec_infer/',  # 文本识别模型路径
    cls_model_dir=r'PaddleOCR/inference/ch_ppocr_mobile_v2.0_cls_infer/',  # 方向分类器模型路径
    det_model_dir=r'PaddleOCR/inference/ch_PP-OCRv3_det_infer'  # 文本检测模型路径
)

# 获取源文件夹中的所有图片

# 复制选中的图片到目标文件夹
def ocr_recognition(img_path, keyword="大厦"):
    result = ocr.ocr(img_path, cls=True)  # 识别图像，并使用方向分类器
    # 处理OCR结果
    dasha = keyword
    for line in result[0]:
        if re.findall(keyword, line[-1][0]):
            dasha = line[-1][0]
            break
    return dasha

# 使用 PaddleOCR 获取楼宇文本的函数
# 初始化 PaddleOCR 模型

logging.disable(logging.CRITICAL)
# 创建检测对象，加载预训练的权重
c = detect_with_API.detectapi(weights='weights_fire/best.pt')
# 定义图片文件夹的路径

print('准备识别火灾_2')
file_path = '24pic/processed03.jpg'
while not os.path.exists(file_path):
    a = 0
time.sleep(1)
print('开始识别火灾_2')
# 火灾检测部分
image_folder = '24pic'
image_files = [os.path.join(image_folder, img) for img in os.listdir(image_folder) if
               img.endswith(('.png', '.jpg', '.jpeg'))]
with torch.no_grad():
    for image_path in image_files:
        image_name = os.path.basename(image_path)
        img = cv2.imread(image_path)
        if img is not None:
            result, names = c.detect([img])
            detections = result[0][1]
            fire_detected = False
            fire_floor_mapping = {}
            dasha = ocr_recognition(image_path)
            if detections is not None:
                for detection in detections:
                    if len(detection) == 3 and isinstance(detection[1], list) and len(detection[1]) == 4:
                        cls_id, bbox, conf = detection
                        label = names[cls_id]
                        if label == 'fire':
                            fire_detected = True
                            x1, y1, x2, y2 = bbox
                            fire_x = (x1 + x2) / 2
                            fire_y = (y1 + y2) / 2
                            fire_floor_mapping[fire_y] = None
                if fire_detected:
                    result_floor, _ = c.detect([img])
                    detections_floor = result_floor[0][1]

                    floor_info = []
                    for detection_floor in detections_floor:
                        label_floor = names[detection_floor[0]]
                        if label_floor == 'floor':
                            x1, y1, x2, y2 = detection_floor[1]
                            floor_y = (y1 + y2) / 2
                            floor_info.append(floor_y)

                    floor_info.sort(reverse=True)

                    for fire_y in fire_floor_mapping.keys():
                        min_diff = float('inf')
                        min_diff_floor = None
                        for i, floor_y in enumerate(floor_info):
                            diff = abs(fire_y - floor_y)
                            if diff < min_diff:
                                min_diff = diff
                                min_diff_floor = i + 1
                        fire_floor_mapping[fire_y] = min_diff_floor

                    fire_floors = list(fire_floor_mapping.values())
                    fire_floors.sort()
                    print(f"{dasha}{'、'.join(map(str, fire_floors))}楼着火")
                else:
                    print(f"{dasha}，没有火灾发生。")
            else:
                print(f"图片“{image_name}”未检测到火灾")

os.remove(file_path)

