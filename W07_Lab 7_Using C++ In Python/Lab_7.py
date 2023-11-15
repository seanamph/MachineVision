#from C++Lib import AddClass
from ctypes import * 

lib = CDLL('c:\python_test\MyDLL.dll');

lib.CreateMathTool.restype = POINTER(c_ulong)
lib.DestroyMathTool.argtypes = [POINTER(c_ulong)]
lib.Add.argtypes = [POINTER(c_ulong), c_int, c_int]
lib.Add.restype = c_int

class AddClass(object):

	def __init__(self):
		self.obj = lib.CreateMathTool()

	def __del__(self):
		lib.DestroyMathTool(self.obj)

	def Add(self, a, b):
		return lib.Add(self.obj, a, b)



obj = AddClass()

c = obj.Add(10, 20)

print(c)
                 