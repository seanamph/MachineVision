#include "Unmanaged_Calculator.h"

int Unmanaged_Calculator::Add(int a, int b)
{
		return a + b;
}

// Unmanaged_Calculator.cpp ªº¤U¤è
extern "C"
{
    __declspec(dllexport) Unmanaged_Calculator* CreateCalculatorInstance()
    {
        return new Unmanaged_Calculator();
    }

    __declspec(dllexport) void DestroyCalculatorInstance(Unmanaged_Calculator* instance)
    {
        delete instance;
    }

    __declspec(dllexport) int Calculator_Add(Unmanaged_Calculator* instance, int a, int b)
    {
        return instance->Add(a, b);
    }
}
