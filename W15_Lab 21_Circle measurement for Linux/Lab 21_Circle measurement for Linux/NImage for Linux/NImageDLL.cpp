// Linux Version
//
#include "NImage.h"
#include "NImageDLL.h"



MYDLL_API unsigned long CreateNImage()
{
	return (unsigned long) new NImage();
}

MYDLL_API unsigned long CreateNImageEx(int wid, int hei)
{
	return (unsigned long) new NImage(wid, hei);
}


MYDLL_API bool DestroyNImage(unsigned long m_Img)
{
	NImage* Img = (NImage*) m_Img;
	
	
	if (Img) delete Img;

	return true;

}

MYDLL_API bool LoadBMP(unsigned long m_Img ,char* filename)
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


MYDLL_API int GetWidth(unsigned long m_Img)
{
	NImage* Img = (NImage*)m_Img;

	return Img->GetWidth();
}

MYDLL_API int GetHeight(unsigned long m_Img)
{
	NImage* Img = (NImage*)m_Img;

	return Img->GetHeight();
}

MYDLL_API int GetSize(unsigned long m_Img)
{
	NImage* Img = (NImage*)m_Img;

	return (Img->GetWidth() * Img->GetHeight() * Img->GetBPP()/8);
}

MYDLL_API bool MemCopy(unsigned long m_Img, u_char *ptr, int wid, int hei)
{
	NImage* Img = (NImage*)m_Img;

	if (ptr != 0 || Img->GetPixelAddress(0,0) != 0)
	{
		int BytesPerPixel = Img->GetBPP() / 8;

		for (int j = 0; j < hei; j++)
			memcpy(ptr + j * wid * BytesPerPixel, Img->GetPixelAddress(0, j), wid * BytesPerPixel);

	}
	else 
		return false;

	return true;
}

MYDLL_API bool ReSize(unsigned long m_Img, int wid, int hei)
{
	NImage* Img = (NImage*)m_Img;

	return (Img->ReSize(wid, hei));
}


