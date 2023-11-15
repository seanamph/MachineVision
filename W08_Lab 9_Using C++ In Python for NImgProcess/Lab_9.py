import matplotlib.pyplot as plt
import numpy as np
from ctypes import * 
from NImage import ImageClass
from NImgProcess import ImgProcessClass

NImg = ImageClass()
NImg2 = ImageClass()
NImgPro = ImgProcessClass()

array = NImg.LoadBMP('Pattern.bmp')

array2 = NImg2.ReSize(NImg.GetWidth(), NImg.GetHeight())

plt.subplot(2,2,1)
plt.title('original image')
plt.imshow(array, cmap='gray')     
plt.xticks([])
plt.yticks([])

if (NImgPro.Inverse(NImg.GetHandle())): inverse_array = NImg.ReturnArray()
plt.subplot(2,2,2)
plt.title('inverse image')
plt.imshow(inverse_array, cmap='gray')    
plt.xticks([])
plt.yticks([]) 

if (NImgPro.SingleThresholding(NImg.GetHandle(), 100)): sin_thres_array = NImg.ReturnArray()
plt.subplot(2,2,3)
plt.title('single threshold image')
plt.imshow(sin_thres_array, cmap='gray')    
plt.xticks([])
plt.yticks([]) 

if (NImgPro.OtsuThresholding(NImg.GetHandle(),NImg2.GetHandle())): otsu_thres_array = NImg2.ReturnArray()
plt.subplot(2,2,4)
plt.title('otsu threshold image')
plt.imshow(otsu_thres_array, cmap='gray')     

plt.xticks([])
plt.yticks([])
plt.show()                   
