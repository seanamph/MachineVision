import numpy as np
from ctypes import * 

lib = CDLL('NImageDLL.so');

lib.CreateNImage.restype = POINTER(c_ulong)
lib.DestroyNImage.argtypes = [POINTER(c_ulong)]
lib.LoadBMP.argtypes = [POINTER(c_ulong), POINTER(c_char)]
lib.LoadBMP.restype = c_bool
lib.MemCopy.argtypes = [POINTER(c_ulong), POINTER(c_uint8), c_int, c_int]
lib.MemCopy.restype = c_bool
lib.ReSize.argtypes = [POINTER(c_ulong), c_int, c_int]
lib.ReSize.restype = c_bool

class ImageClass(object):

	def __init__(self):
		self.obj = lib.CreateNImage()

	def __del__(self):
		lib.DestroyNImage(self.obj)

	def LoadBMP(self, path):
		b_string1 = path.encode('utf-8')
		if(lib.LoadBMP(self.obj, create_string_buffer(b_string1)) == 0): return
		x = np.arange(0, lib.GetSize(self.obj), 1, c_uint8)
		if (lib.MemCopy(self.obj, x.ctypes.data_as(POINTER(c_uint8)), lib.GetWidth(self.obj), 
		lib.GetHeight(self.obj))): my_2D_x = x.reshape((lib.GetHeight(self.obj),lib.GetWidth(self.obj)))
		return my_2D_x
		
	def ReSize(self, wid, hei):
	    if(lib.ReSize(self.obj, wid, hei) == 0): return
	    x = np.arange(0, wid*hei, 1, c_uint8)
	    if (lib.MemCopy(self.obj, x.ctypes.data_as(POINTER(c_uint8)), wid, hei)): my_2D_x = x.reshape(hei,wid)
	    return my_2D_x
