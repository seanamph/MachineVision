import matplotlib.pyplot as plt
import numpy as np
from ctypes import * 
from NImage import ImageClass

NImg = ImageClass()

array = NImg.LoadBMP('Pattern.bmp');

print(array)

plt.imshow(array, cmap='gray')       
plt.show()                   
