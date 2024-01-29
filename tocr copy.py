import cv2
import numpy as np
import pytesseract
from matplotlib import pyplot as plt

# 讀取圖像
image = cv2.imread('C:\\Users\\seana\\Downloads\\1344449_0.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 找出輪廓
contours, _ = cv2.findContours(gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

def merge_contours(bounding_boxes, threshold=1):
    """
    合併相鄰或重疊的輪廓。
    :param bounding_boxes: 邊界框列表，每個邊界框格式為 (x, y, width, height)
    :param threshold: 相鄰邊界框的最大距離
    :return: 合併後的邊界框列表
    """
    merged = []

    while bounding_boxes:
        # 從列表中移除並處理第一個邊界框
        box = bounding_boxes.pop(0)
        x, y, w, h = box

        # 檢查其餘的邊界框是否與當前邊界框相鄰或重疊
        to_merge = [box]
        for other_box in bounding_boxes:
            if is_near(box, other_box, threshold):
                to_merge.append(other_box)

        # 從列表中移除將要合併的邊界框
        for box_to_merge in to_merge:
            if box_to_merge in bounding_boxes:
                bounding_boxes.remove(box_to_merge)

        # 計算合併後的邊界框
        merged_x = min([box[0] for box in to_merge])
        merged_y = min([box[1] for box in to_merge])
        merged_w = max([box[0] + box[2] for box in to_merge]) - merged_x
        merged_h = max([box[1] + box[3] for box in to_merge]) - merged_y
        merged.append((merged_x, merged_y, merged_w, merged_h))

    return merged

def is_near(box1, box2, threshold):
    """
    檢查兩個邊界框是否足夠接近以合併。
    :param box1: 第一個邊界框 (x, y, width, height)
    :param box2: 第二個邊界框 (x, y, width, height)
    :param threshold: 相鄰邊界框的最大距離
    :return: 布爾值，表示兩個邊界框是否應該合併
    """
    x1, y1, w1, h1 = box1
    x2, y2, w2, h2 = box2

    return (x1 <= x2 + w2 + threshold and x1 + w1 + threshold >= x2 and
            y1 <= y2 + h2 + threshold and y1 + h1 + threshold >= y2)

# 計算輪廓的邊界框，並合併相鄰輪廓
bounding_boxes = [cv2.boundingRect(contour) for contour in contours]
merged_boxes = merge_contours(bounding_boxes) # merge_contours 是你需要實現的函數

# 對每個合併後的輪廓進行 OCR
for box in merged_boxes:
    x, y, w, h = box
    roi = gray[y:y+h, x:x+w]
    #pytesseract.pytesseract.tesseract_cmd = 'C:\\Program Files\\Tesseract-OCR\\tesseract.exe'
    #text = pytesseract.image_to_string(roi, lang='chi_tra', config='--tessdata-dir "C:\\Program Files\\Tesseract-OCR\\tessdata_best-main"')
    cv2.rectangle(image, (x, y), (x+w, y+h), (0, 255, 0), 2)
    #cv2.putText(image, text, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

# 顯示結果
plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
plt.show()
