import numpy as np
from ctypes import * 

lib4 = CDLL('NGaugeDLL.so');

lib4.CreateNGauge.restype = POINTER(c_ulong)
lib4.DestroyNGauge.argtypes = [POINTER(c_ulong)]
#(unsigned long m_Img, unsigned long m_MaskImg, unsigned long m_Gauge, double *sub_x, double *sub_y)
lib4.SubPixel_EdgeDetector.argtypes = [POINTER(c_ulong), POINTER(c_ulong), POINTER(c_ulong), POINTER(c_double), POINTER(c_double)]			
lib4.SubPixel_EdgeDetector.restype = c_int
#(unsigned long m_Gauge, double *edgelist_x, double *edgelist_y, int edge_num, double *result_x,double *result_y, double *result_r)
lib4.CircleFitByKasa.argtypes = [POINTER(c_ulong), POINTER(c_double), POINTER(c_double), c_int, POINTER(c_double), POINTER(c_double), POINTER(c_double)] 
lib4.CircleFitByKasa.restype = c_bool


class GaugeClass(object):

	def __init__(self):
		self.obj = lib4.CreateNGauge()

	def __del__(self):
		lib4.DestroyNGauge(self.obj)
	
	def SubPixel_EdgeDetector(self, Img, MaskImg, sub_x, sub_y): 
		return lib4.SubPixel_EdgeDetector(Img, MaskImg, self.obj, sub_x, sub_y)
		
	def CircleFitByKasa(self, edgelist_x, edgelist_y, edge_num, result_x, result_y, result_r):
		return lib4.CircleFitByKasa(self.obj, edgelist_x, edgelist_y, edge_num, result_x, result_y, result_r)