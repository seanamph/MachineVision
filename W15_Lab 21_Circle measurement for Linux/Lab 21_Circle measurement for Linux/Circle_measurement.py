import matplotlib.pyplot as plt
import numpy as np
from ctypes import * 
from NImage import ImageClass
from NImgProcess import ImgProcessClass
from NObject import ObjectClass
from NGauge import GaugeClass

NImg = ImageClass()
NOtsuImg = ImageClass()
NImgPro = ImgProcessClass()
NObj = ObjectClass()
NGauge = GaugeClass()

array = NImg.LoadBMP('1.bmp')

array2 = NOtsuImg.ReSize(NImg.GetWidth(), NImg.GetHeight())

plt.subplot(2,1,1)
plt.title('Original image')
plt.imshow(array, cmap='gray')     
plt.xticks([])
plt.yticks([])


ct_x = np.arange(0, 10000, 1, c_int)
ct_y = np.arange(0, 10000, 1, c_int)
sub_x = np.arange(0, 10000, 1, c_double)
sub_y = np.arange(0, 10000, 1, c_double)

chain_count = 0
result_x = np.arange(0, 1, 1, c_double)
result_y = np.arange(0, 1, 1, c_double)
result_r = np.arange(0, 1, 1, c_double)

plt.subplot(2,1,2)
plt.title('Circle measurement')
plt.imshow(array2)    
plt.xticks([])
plt.yticks([]) 

if (NImgPro.OtsuThresholding(NImg.GetHandle(), NOtsuImg.GetHandle())): 
	blob_count = NObj.Blob_Labelling(NOtsuImg.GetHandle())

for i in range(blob_count):
	chain_count = NObj.Contour_Tracing(NOtsuImg.GetHandle(), i, ct_x.ctypes.data_as(POINTER(c_int)), ct_y.ctypes.data_as(POINTER(c_int)))
	for j in range(chain_count):
		sub_x[j] = ct_x[j]
		sub_y[j] = ct_y[j]
	
	if (NGauge.CircleFitByKasa(sub_x.ctypes.data_as(POINTER(c_double)), sub_y.ctypes.data_as(POINTER(c_double)), chain_count, result_x.ctypes.data_as(POINTER(c_double)), result_y.ctypes.data_as(POINTER(c_double)), result_r.ctypes.data_as(POINTER(c_double)))):
		circle = plt.Circle((result_x[0], result_y[0]), result_r[0], color='r', fill=False)
		plt.gcf().gca().add_artist(circle)

plt.show()                   
