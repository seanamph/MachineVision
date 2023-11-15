// NImageDLL.cpp : 定義 DLL 應用程式的匯出函式。
//
#include "NImage.h"
#include "NImageDLL.h"


	// 這是匯出函式的範例。
	MYDLL_API LONG_PTR __cdecl CreateNImage()
	{
		return (LONG_PTR) new NImage();
	}


	MYDLL_API bool  __cdecl DestroyNImage(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;


		if (Img) delete Img;

		return true;

	}

	MYDLL_API bool  __cdecl LoadBMP(LONG_PTR m_Img, char* filename)
	{
		int bFlag = false;

		NImage* Img = (NImage*)m_Img;

		if (Img != 0)
			bFlag = Img->LoadBMP(filename);

		if (bFlag)
			return true;
		else
			return false;
	}

	MYDLL_API bool  __cdecl SaveBMP(LONG_PTR m_Img, char* filename)
	{
		int bFlag = false;

		NImage* Img = (NImage*)m_Img;

		if (Img != 0)
			bFlag = Img->SaveBMP(filename);

		if (bFlag)
			return true;
		else
			return false;
	}

	MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		return (HBITMAP*)*(Img->GetBitmap());
	}


	MYDLL_API void __cdecl MeanFilter3x3(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		Img->MeanFilter3x3();
	}


	MYDLL_API void __cdecl SobelFilter(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		Img->SobelFilter();
	}


	MYDLL_API void __cdecl LaplacianFilter(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		Img->LaplacianFilter();
	}

	MYDLL_API void __cdecl Threshold(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		Img->Threshold();
	}
	MYDLL_API void __cdecl AdaptiveMeanThreshold(LONG_PTR m_Img, int blockSize)
	{
		NImage* Img = (NImage*)m_Img;

		Img->AdaptiveMeanThreshold(blockSize);
	}
	MYDLL_API void __cdecl AdaptiveGaussianThreshold(LONG_PTR m_Img, int blockSize)
	{
		NImage* Img = (NImage*)m_Img;

		Img->AdaptiveGaussianThreshold(blockSize);
	}
	MYDLL_API int __cdecl Blob_Labelling(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		return Img->Blob_Labelling();
	}
	MYDLL_API int __cdecl Contour_Tracing(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		return Img->Contour_Tracing();
	}
	MYDLL_API int __cdecl CalculateBlobArea(LONG_PTR m_Img)
	{
		NImage* Img = (NImage*)m_Img;

		return Img->CalculateBlobArea();
	}