// NImageDLL.cpp : 定義 DLL 應用程式的匯出函式。
//
#include "NImageDLL.h"
#include "NImage.h"


// 這是匯出函式的範例。
MYDLL_API LONG_PTR __cdecl CreateNImage()
{
	return (LONG_PTR) new NImage();
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
