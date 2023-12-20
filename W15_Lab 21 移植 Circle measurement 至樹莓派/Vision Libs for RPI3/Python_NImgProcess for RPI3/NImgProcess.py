import numpy as np
from ctypes import * 

lib2 = CDLL('NImgProcessDLL.so');

lib2.CreateNImgProcess.restype = POINTER(c_ulong)
lib2.DestroyNImgProcess.argtypes = [POINTER(c_ulong)]
lib2.Inverse.argtypes = [POINTER(c_ulong), POINTER(c_uint8), c_int, c_int]
lib2.Inverse.restype = c_bool
lib2.SingleThresholding.argtypes = [POINTER(c_ulong), POINTER(c_uint8), c_int, c_int, c_int]
lib2.SingleThresholding.restype = c_bool
lib2.OtsuThresholding.argtypes = [POINTER(c_ulong), POINTER(c_uint8), c_int, c_int]
lib2.OtsuThresholding.restype = c_bool

class ImgProcessClass(object):

	def __init__(self):
		self.obj = lib2.CreateNImgProcess()

	def __del__(self):
		lib2.DestroyNImgProcess(self.obj)
	
	def Inverse(self, data): 
		pro_data = data.copy()
		wid = pro_data.shape[1]
		hei = pro_data.shape[0]
		if(lib2.Inverse(self.obj, pro_data.ctypes.data_as(POINTER(c_uint8)), wid, hei)): return pro_data
		
	def SingleThresholding(self, data, thres):
		pro_data = data.copy()
		wid = pro_data.shape[1]
		hei = pro_data.shape[0]
		if(lib2.SingleThresholding(self.obj, pro_data.ctypes.data_as(POINTER(c_uint8)), wid, hei, thres)): return pro_data
		
	def OtsuThresholding(self, data):
		pro_data = data.copy()
		wid = pro_data.shape[1]
		hei = pro_data.shape[0]
		if(lib2.OtsuThresholding(self.obj, pro_data.ctypes.data_as(POINTER(c_uint8)), wid, hei)): return pro_data
