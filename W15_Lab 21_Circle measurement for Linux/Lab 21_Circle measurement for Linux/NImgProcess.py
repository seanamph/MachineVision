import numpy as np
from ctypes import * 

lib2 = CDLL('NImgProcessDLL.so');

lib2.CreateNImgProcess.restype = POINTER(c_ulong)
lib2.DestroyNImgProcess.argtypes = [POINTER(c_ulong)]
lib2.Inverse.argtypes = [POINTER(c_ulong), POINTER(c_ulong)]
lib2.Inverse.restype = c_bool
lib2.SingleThresholding.argtypes = [POINTER(c_ulong), POINTER(c_ulong), c_int]
lib2.SingleThresholding.restype = c_bool
lib2.OtsuThresholding.argtypes = [POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong)]
lib2.OtsuThresholding.restype = c_bool

class ImgProcessClass(object):

	def __init__(self):
		self.obj = lib2.CreateNImgProcess()

	def __del__(self):
		lib2.DestroyNImgProcess(self.obj)
	
	def Inverse(self, Img): 
		if(lib2.Inverse(Img, self.obj)): return True
		
	def SingleThresholding(self, Img, thres):
		if(lib2.SingleThresholding(Img, self.obj, thres)): return True
		
	def OtsuThresholding(self, Img1, Img2):
		if(lib2.OtsuThresholding(Img1, Img2, self.obj)): return True
