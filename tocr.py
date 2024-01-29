import pytesseract
from PIL import Image, ImageEnhance, ImageFilter
import json
# 指定 tesseract.exe 的路徑（如果已經加入環境變數，則可以省略此行）
pytesseract.pytesseract.tesseract_cmd = 'C:\\Program Files\\Tesseract-OCR\\tesseract.exe'

# 圖像預處理
def preprocess_image(image_path):
    img = Image.open(image_path)
    img = img.convert('L')  # 轉換為灰度圖
    enhancer = ImageEnhance.Contrast(img)
    img = enhancer.enhance(2)  # 增強對比度
    return img

# 開啟圖像文件
image_path = 'C:\\Users\\seana\\Downloads\\054_0.png'
img = preprocess_image(image_path)
# 使用 Tesseract 進行圖像識別
text = pytesseract.image_to_string(img, lang='chi_tra', config='--tessdata-dir "C:\\Program Files\\Tesseract-OCR\\tessdata_best-main"')

# 輸出識別結果
print(text)
