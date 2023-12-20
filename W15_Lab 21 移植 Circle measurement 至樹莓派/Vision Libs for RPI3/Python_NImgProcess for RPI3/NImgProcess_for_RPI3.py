import matplotlib.pyplot as plt
import numpy as np
from ctypes import * 
from NImage import ImageClass
from NImgProcess import ImgProcessClass

NImg = ImageClass()
NImgPro = ImgProcessClass()

array = NImg.LoadBMP('Pattern.bmp')

plt.subplot(2,2,1)
plt.title('original image')
plt.imshow(array, cmap='gray')     
plt.xticks([])
plt.yticks([])

inverse_array = NImgPro.Inverse(array)
plt.subplot(2,2,2)
plt.title('inverse image')
plt.imshow(inverse_array, cmap='gray')    
plt.xticks([])
plt.yticks([]) 

sin_thres_array = NImgPro.SingleThresholding(array, 100)
plt.subplot(2,2,3)
plt.title('single threshold image')
plt.imshow(sin_thres_array, cmap='gray')    
plt.xticks([])
plt.yticks([]) 

otsu_thres_array = NImgPro.OtsuThresholding(array)
plt.subplot(2,2,4)
plt.title('otsu threshold image')
plt.imshow(otsu_thres_array, cmap='gray')     

plt.xticks([])
plt.yticks([])
plt.show()                   
