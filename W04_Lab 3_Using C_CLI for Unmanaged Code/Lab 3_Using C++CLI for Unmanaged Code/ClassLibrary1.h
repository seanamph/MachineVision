#include "Unmanaged_Calculator.h"

#pragma once
#pragma comment(lib, "Dll1.lib")

using namespace System;


namespace ClassLibrary1 
{
	public ref class ManagedClass
	{
	public:
		// Allocate the native object on the C++ Heap via a constructor
		ManagedClass() : m_Impl(new Unmanaged_Calculator) {}

		// Deallocate the native object on a destructor
		~ManagedClass() 
		{
			delete m_Impl;
		}
	protected:
		// Deallocate the native object on the finalizer just in case no destructor is called
		!ManagedClass() 
		{
			delete m_Impl;
		}

	public:
		
		int Add(int a, int b) 
		{
			return (m_Impl->Add (a, b));
		}

	private:
		Unmanaged_Calculator	*m_Impl;
	};
}
