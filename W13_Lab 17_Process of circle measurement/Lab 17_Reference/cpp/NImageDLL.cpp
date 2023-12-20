// NImageDLL.cpp : 定義 DLL 應用程式的匯出函式。
//
#include "NImageDLL.h"
#include "NImage.h"


// 這是匯出函式的範例。
MYDLL_API LONG_PTR __cdecl CreateNImage()
{
	return (LONG_PTR) new NImage();
}

MYDLL_API LONG_PTR __cdecl CreateNImageEx(int wid, int hei)
{
	return (LONG_PTR) new NImage(wid, hei);
}


MYDLL_API bool  __cdecl DestroyNImage(LONG_PTR m_Img)
{
	NImage* Img = (NImage*) m_Img;
	
	
	if (Img) delete Img;

	return true;

}

MYDLL_API bool  __cdecl LoadBMP(LONG_PTR m_Img ,char* filename)
{
	int bFlag = false;

	NImage* Img = (NImage*) m_Img;
	
	if (Img != 0)
		bFlag = Img->LoadBMP(filename);
	
	if (bFlag)
		return true;
	else
		return false;
}

MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR m_Img)
{
	NImage* Img = (NImage*) m_Img;
	
	return (HBITMAP*)*(Img->GetBitmap()) ;
}


MYDLL_API int __cdecl GetWidth(LONG_PTR m_Img)
{
	NImage* Img = (NImage*)m_Img;

	return Img->GetWidth();
}

MYDLL_API int __cdecl GetHeight(LONG_PTR m_Img)
{
	NImage* Img = (NImage*)m_Img;

	return Img->GetHeight();
}

MYDLL_API int __cdecl GetSize(LONG_PTR m_Img)
{
	NImage* Img = (NImage*)m_Img;

	return (Img->GetWidth() * Img->GetHeight() * Img->GetBPP()/8);
}

MYDLL_API bool __cdecl MemCopy(LONG_PTR m_Img, BYTE *ptr, int wid, int hei)
{
	NImage* Img = (NImage*)m_Img;

	if (ptr != 0 || Img->GetPixelAddress(0,0) != 0)
	{
		int BytesPerPixel = Img->GetBPP() / 8;

		for (int j = 0; j < hei; j++)
			memcpy(ptr + j * wid * BytesPerPixel, Img->GetPixelAddress(0, j), wid * BytesPerPixel);

	}
	else return false;

	return true;
}


