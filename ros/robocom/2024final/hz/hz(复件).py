import cv2
import detect_with_API
import torch
import os
import logging
import re
import shutil
from glob import glob
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

# 设置要清空的文件夹相对路径
folder_path = 'result'
if os.path.exists(folder_path) and os.listdir(folder_path):
    for filename in os.listdir(folder_path):
        file_path = os.path.join(folder_path, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            pass

# 源文件夹和目标文件夹路径
source_dir = '24pic'
target_dir = 'inference'

# 获取源文件夹中的所有图片
source_images = glob(os.path.join(source_dir, '*.jpg'))

# 确保目标文件夹存在，如果不存在，则创建
os.makedirs(target_dir, exist_ok=True)

# 复制选中的图片到目标文件夹
for img_path in source_images:
    shutil.copy(img_path, target_dir)


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
def get_license_result(ocr, image):
    result = ocr.ocr(image, cls=True)[0]
    if result:
        license_name, conf = result[0][1]
        if '·' in license_name:
            license_name = license_name.replace('·', '')
        return license_name, conf
    else:
        return None, None


# 初始化 PaddleOCR 模型
cls_model_dir = 'paddleModels/whl/cls/ch_ppocr_mobile_v2.0_cls_infer'
rec_model_dir = 'paddleModels/whl/rec/ch/ch_PP-OCRv4_rec_infer'
logging.disable(logging.CRITICAL)
ocr = PaddleOCR(use_angle_cls=False, lang="ch", det=False, cls_model_dir=cls_model_dir, rec_model_dir=rec_model_dir)
# 创建检测对象，加载预训练的权重
a = detect_with_API.detectapi(weights='weights_word/best.pt')
b = detect_with_API.detectapi(weights='weights_picture/best.pt')
c = detect_with_API.detectapi(weights='weights_fire/best.pt')

# 定义图片文件夹的路径
image_folder = 'inference'
image_files = [os.path.join(image_folder, img) for img in os.listdir(image_folder) if
               img.endswith(('.png', '.jpg', '.jpeg'))]

# 楼宇识别和文字识别部分
license_results = {}
with torch.no_grad():
    for image_path in image_files:
        image_name = os.path.basename(image_path)
        img = cv2.imread(image_path)
        if img is not None:
            # 楼宇识别
            result, names = b.detect([img])
            detections = result[0][1]
            license_imgs = []
            if detections is not None:
                for detection in detections:
                    if len(detection) == 3 and isinstance(detection[1], list) and len(detection[1]) == 4:
                        cls_id, bbox, conf = detection
                        x1, y1, x2, y2 = bbox
                        cropImg = img[y1:y2, x1:x2]
                        license_imgs.append(cropImg)
                        # 确保result目录存在
                        result_directory = 'result'
                        if not os.path.exists(result_directory):
                            os.makedirs(result_directory)
                        # 设置保存的图片路径
                        save_path = os.path.join(result_directory, image_name)
                        # 保存检测后的图片
                        cv2.imwrite(save_path, cropImg)
            else:
                print(f"图片”{image_name}“未检测到目标")

            # 楼宇文字识别
            for each in license_imgs:
                license_num, conf = get_license_result(ocr, each)
                if license_num:
                    license_results[image_name] = license_num

# 火灾检测部分
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
                    license_num = license_results.get(image_name, "未知")
                    print(f"{dasha}{'、'.join(map(str, fire_floors))}楼着火")
                else:
                    license_num = license_results.get(image_name, "未知")
                    #print(f"{dasha}，没有火灾发生。")
            else:
                print(f"图片“{image_name}”未检测到火灾")

files_to_remove = glob(os.path.join(source_dir, '*'))
for file_path in files_to_remove:
    try:
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)
    except Exception as e:
        print(f'无法删除文件: {file_path}. 原因是: {e}')

files_to_remove = glob(os.path.join(target_dir, '*'))
for file_path in files_to_remove:
    try:
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)
    except Exception as e:
        print(f'无法删除文件: {file_path}. 原因是: {e}')



