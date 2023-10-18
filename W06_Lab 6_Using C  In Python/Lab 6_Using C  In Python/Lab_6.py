import time
#from ctypes import cdll
from ctypes import * 

def Fibo_Python(n):
    if n<2:
        return 1
    else:
        return Fibo_Python(n-1) + Fibo_Python(n-2)

start_time = time.time()
a = Fibo_Python(40)
end_time = time.time()

duration = end_time-start_time
print(a)
print(f'Time consumption by Python: {round(duration,3)}s')


#MyDLL = cdll.LoadLibrary('C:\Python_test\MyDLL.dll')
MyDLL = CDLL('C:\Python_test\MyDLL.dll')
MyDLL.Fibo_C.argtypes = [c_int]
MyDLL.Fibo_C.restype = c_int

start_time = time.time()
b = MyDLL.Fibo_C(40)
end_time = time.time()

duration = end_time-start_time
print(b)
print(f'Time consumption by DLL: {round(duration,3)}s')