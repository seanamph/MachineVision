import matplotlib.pyplot as plt
import numpy as np
from ctypes import * 
from NImage import ImageClass

NImg = ImageClass()

array = NImg.LoadBMP('c:\python_test\pattern.bmp');

print(array.size)

plt.imshow(array, cmap='gray')     
plt.show()                   