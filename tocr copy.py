import cv2
import pytesseract
from PIL import Image
import matplotlib.pyplot as plt

# 讀取圖像
image = cv2.imread( 'C:\\Users\\seana\\Downloads\\1344440.jpg')

# 轉換為灰度圖像
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 二值化
ret, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY_INV)

# 尋找輪廓
contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 將 OpenCV 圖像轉換為 RGB 格式（用於 matplotlib）
image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# 使用 matplotlib 顯示圖像
plt.figure(figsize=(10,10))
plt.imshow(image_rgb)

for contour in contours:
    # 獲得輪廓的邊界框
    x, y, w, h = cv2.boundingRect(contour)
    
    # 裁剪出輪廓
    cropped = image[y-10:y+h+10, x+10:x+w+10]

    # 使用 PIL 轉換格式
    pil_img = Image.fromarray(cropped)

    pytesseract.pytesseract.tesseract_cmd = 'C:\\Program Files\\Tesseract-OCR\\tesseract.exe'
    # pytesseract 進行 OCR 辨識
    text = pytesseract.image_to_string(pil_img, lang='chi_tra', config='--tessdata-dir "C:\\Program Files\\Tesseract-OCR\\tessdata_best-main"').strip()

    # 在圖像上畫出邊界框並添加文字
    plt.gca().add_patch(plt.Rectangle((x, y), w, h, fill=None, edgecolor='green', linewidth=2))

# 顯示帶有邊界框和文字的圖像
plt.show()
