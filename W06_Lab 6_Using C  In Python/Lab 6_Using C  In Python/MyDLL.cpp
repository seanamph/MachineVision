// MyDLL.cpp : 定義 DLL 應用程式的匯出函式。
//
#include "MyDLL.h"


// 這是匯出函式的範例。
MYDLL_API int __cdecl Fibo_C(int n)
{
	if (n < 2)
		return 1;
	else
		return Fibo_C(n - 1) + Fibo_C(n - 2);
}




