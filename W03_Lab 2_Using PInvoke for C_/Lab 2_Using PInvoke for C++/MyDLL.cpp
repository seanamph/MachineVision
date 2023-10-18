// MyDLL.cpp : �w�q DLL ���ε{�����ץX�禡�C
//
#include "pch.h"
#include "Unmanaged_Calculator.h"
#include "MyDLL.h"

// �o�O�ץX�禡���d�ҡC
MYDLL_API LONG_PTR __cdecl CreateMathTool()
{
	return (LONG_PTR) new Unmanaged_Calculator();
}
MYDLL_API bool  __cdecl DestroyMathTool(LONG_PTR m_Math)
{
	Unmanaged_Calculator *Calculator = (Unmanaged_Calculator*)m_Math;

	if (Calculator) delete Calculator;

	return true;
}

MYDLL_API int  __cdecl Add(LONG_PTR m_Math, int a, int b)
{
	Unmanaged_Calculator *Calculator = (Unmanaged_Calculator*)m_Math;

	return (Calculator->Add(a, b));

}



