import time
import ctypes 

MyDLL = ctypes.CDLL(f"C:\GitHub\MachineVision\W06_Lab 6_Using C  In Python\Lab 6_Using C  In Python\MyDLL.dll")
b = MyDLL.Fibo_C(40)
print(b)