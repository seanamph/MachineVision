// MyDLL.cpp : �w�q DLL ���ε{�����ץX�禡�C
//
#include "MyDLL.h"


// �o�O�ץX�禡���d�ҡC
MYDLL_API int __cdecl Fibo_C(int n)
{
	if (n < 2)
		return 1;
	else
		return Fibo_C(n - 1) + Fibo_C(n - 2);
}




