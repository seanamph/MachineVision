import cv2
import numpy as np
import matplotlib.pyplot as plt
from skimage import io, color, filters, morphology
from skimage.measure import label, regionprops
from skimage import measure
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

""" 
def is_contour_inside_other(contour, other_contours):
    x1, y1, w1, h1 = cv2.boundingRect(contour)
    for other_contour in other_contours:
        x2, y2, w2, h2 = cv2.boundingRect(other_contour)
        if x1 >= x2 and y1 >= y2 and x1 + w1 <= x2 + w2 and y1 + h1 <= y2 + h2:
            return True
    return False

# 讀取圖像
image = cv2.imread('C:\\Users\\seana\\Downloads\\1324122_0.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
blurred = cv2.GaussianBlur(gray, (5, 5), 0)

# 邊緣檢測
edged = cv2.Canny(blurred, 30, 150)

# 找到輪廓
contours, _ = cv2.findContours(edged.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 篩選並繪製輪廓
for contour in contours:
    x, y, w, h = cv2.boundingRect(contour)
    cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 边缘检测
edges = cv2.Canny(gray, 50, 150, apertureSize=3)

# 使用霍夫线变换
lines = cv2.HoughLinesP(edges, 1, np.pi / 180, threshold=100, minLineLength=100, maxLineGap=10)

# 绘制线条
for line in lines:
    x1, y1, x2, y2 = line[0]
    cv2.line(image, (x1, y1), (x2, y2), (0, 0, 255), 2)

# 顯示圖像
cv2.imshow('Text Regions', image)
cv2.waitKey(0)
cv2.destroyAllWindows()

image = cv2.imread('C:\\Users\\seana\\Downloads\\1324122_0.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 应用阈值处理
_, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)

# 检测轮廓
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 在原图上绘制轮廓
cv2.drawContours(image, contours, -1, (0, 255, 0), 3)

# 使用 Matplotlib 显示图像
plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
plt.title("Image Contours")
plt.show()

gray = color.rgb2gray(image)

# 应用 Sobel 边缘检测
edges = filters.sobel(gray)

# 应用阈值处理
thresh = filters.threshold_otsu(edges)
binary = edges > thresh

# 应用形态学闭运算
selem = morphology.rectangle(1, 20)
closed = morphology.closing(binary, selem)

# 标记区域
label_img = label(closed)
regions = regionprops(label_img)

# 绘制检测到的区域
fig, ax = plt.subplots()
ax.imshow(gray, cmap='gray')

for region in regions:
    # 绘制矩形框
    minr, minc, maxr, maxc = region.bbox
    rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
                              fill=False, edgecolor='red', linewidth=2)
    ax.add_patch(rect)

ax.set_axis_off()
plt.tight_layout()
plt.show()
 """
def recursive_detect_and_draw(ax, image, bbox, level=0, max_level=2):
    if level > max_level:
        return
    
    minr, minc, maxr, maxc = bbox
    region_img = image[minr:maxr, minc:maxc]

    # 边缘检测和找到轮廓
    ret, thresh = cv2.threshold(region_img, 127, 255, 0)
    contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    
    # 创建一个全黑图像用于绘制轮廓
    mask = np.zeros_like(region_img)

    # 使用 OpenCV 绘制轮廓
    cv2.drawContours(mask, contours, -1, (255), -1)

    # 使用 scikit-image 的 label 和 regionprops
    labels = measure.label(mask, background=0)
    new_regions = measure.regionprops(labels)

    # 递归检测新的区域
    for new_region in new_regions:
        minr_new, minc_new, maxr_new, maxc_new = new_region.bbox
        minr_new += minr
        minc_new += minc
        maxr_new += minr
        maxc_new += minc
        rect = mpatches.Rectangle((minc_new, minr_new), maxc_new - minc_new, maxr_new - minr_new,
                                  fill=False, edgecolor='blue', linewidth=2)
        ax.add_patch(rect)

        # 递归
        recursive_detect_and_draw(ax, image, (minr_new, minc_new, maxr_new, maxc_new), level + 1, max_level)


 
image = cv2.imread('C:\\Users\\seana\\Downloads\\1324122_0.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 边缘检测和找到轮廓
blurred = cv2.GaussianBlur(gray, (5, 5), 0)

# 邊緣檢測
edged = cv2.Canny(blurred, 30, 150)

# 找到輪廓
contours, _ = cv2.findContours(edged.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 创建一个全黑图像用于绘制轮廓
mask = np.zeros_like(gray)

# 使用 OpenCV 绘制轮廓
cv2.drawContours(mask, contours, -1, (255), -1)

# 使用 scikit-image 的 label 和 regionprops
labels = measure.label(mask, background=0)
regions = measure.regionprops(labels)

# 绘制图像
fig, ax = plt.subplots()
ax.imshow(gray, cmap='gray')

# 绘制 OpenCV 轮廓
for contour in contours:
    cv2.drawContours(image, [contour], -1, (0, 255, 0), 2)

# 绘制 scikit-image regions
for region in regions:
    minr, minc, maxr, maxc = region.bbox
    rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
                              fill=False, edgecolor='red', linewidth=2)
    ax.add_patch(rect)

ax.set_axis_off()
plt.show()