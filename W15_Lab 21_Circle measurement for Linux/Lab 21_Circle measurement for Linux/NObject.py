import numpy as np
from ctypes import * 

lib3 = CDLL('NObjectDLL.so');

lib3.CreateNObject.restype = POINTER(c_ulong)
lib3.DestroyNObject.argtypes = [POINTER(c_ulong)]
lib3.Blob_Labelling.argtypes = [POINTER(c_ulong), POINTER(c_ulong)]			#(unsigned long m_Img, unsigned long m_Obj)
lib3.Blob_Labelling.restype = c_int
lib3.Contour_Tracing.argtypes = [POINTER(c_ulong), POINTER(c_ulong), c_int, POINTER(c_int), POINTER(c_int)] #(unsigned long m_Img, unsigned long m_Obj, int blob_num, int *ct_x, int  *ct_y)
lib3.Contour_Tracing.restype = c_int
lib3.Area.argtypes = [POINTER(c_ulong), c_int]	#(unsigned long m_Obj, int blob_num)
lib3.Area.restype = c_int
lib3.Blob_Count.argtypes = [POINTER(c_ulong)]	#(unsigned long m_Obj)
lib3.Blob_Count.restype = c_int
lib3.Rect.argtypes = [POINTER(c_ulong), c_int, POINTER(c_int), POINTER(c_int), POINTER(c_int), POINTER(c_int)]	#(unsigned long m_Obj, int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h)
lib3.Rect.restype = c_bool
lib3.CreateMaskFromObject.argtypes = [POINTER(c_ulong), POINTER(c_ulong), c_int]	#(unsigned long m_Mask_Img, unsigned long m_Obj, int blob_num)
lib3.CreateMaskFromObject.restype = c_bool

class ObjectClass(object):

	def __init__(self):
		self.obj = lib3.CreateNObject()

	def __del__(self):
		lib3.DestroyNObject(self.obj)
	
	def Blob_Labelling(self, Img): 
		return lib3.Blob_Labelling(Img, self.obj)
		
	def Contour_Tracing(self, Img, blob_num, ct_x, ct_y):
		return lib3.Contour_Tracing(Img, self.obj, blob_num, ct_x, ct_y)
		
	def Area(self, blob_num):
		return lib3.Area(self.obj, blob_num)

	def Blob_Count(self):
		return lib3.Blob_Count(self.obj)

	def Rect(self, blob_num, start_x, start_y, rect_w, rect_h):
		return lib3.Rect(self.obj, blob_num, start_x, start_y, rect_w, rect_h)

	def CreateMaskFromObject(self, Img, blob_num):
		return lib3.Rect(Img, self.obj, blob_num)