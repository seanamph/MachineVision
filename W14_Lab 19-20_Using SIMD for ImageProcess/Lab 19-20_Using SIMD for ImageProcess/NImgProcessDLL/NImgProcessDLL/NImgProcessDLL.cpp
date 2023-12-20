// NImageDLL.cpp : 定義 DLL 應用程式的匯出函式。
//
#include "NImgProcessDLL.h"
#include "NImage.h"
#include "NImgProcess.h"


// 這是匯出函式的範例。
NIMGPROCESSDLL_API LONG_PTR __cdecl CreateNImgProcess()
{
	return (LONG_PTR) new NImgProcess();
}


NIMGPROCESSDLL_API bool __cdecl DestroyNImgProcess(LONG_PTR m_ImgPro)
{
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;
	
	if (ImgPro) delete ImgPro;

	return true;

}

NIMGPROCESSDLL_API	bool __cdecl Inverse(LONG_PTR m_Img, LONG_PTR m_ImgPro)
{
	
	NImage *Img = (NImage*) m_Img;
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Inverse(Img));

}

NIMGPROCESSDLL_API	bool __cdecl SingleThresholding(LONG_PTR m_Img, LONG_PTR m_ImgPro, int threshold)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->SingleThresholding(Img, threshold));
}

NIMGPROCESSDLL_API	bool __cdecl OtsuThresholding(LONG_PTR m_Img, LONG_PTR m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->OtsuThresholding(Img));
}

NIMGPROCESSDLL_API	bool __cdecl Sobel(LONG_PTR m_Img, LONG_PTR m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Sobel(Img));
}

NIMGPROCESSDLL_API	bool __cdecl Laplacian(LONG_PTR m_Img, LONG_PTR m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Laplacian(Img));
}

NIMGPROCESSDLL_API	bool __cdecl Mean(LONG_PTR m_Img, LONG_PTR m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Mean(Img));
}

NIMGPROCESSDLL_API	bool __cdecl Subtract(LONG_PTR m_SrcImg, LONG_PTR m_RefImg, LONG_PTR m_ImgPro)
{
	NImage* SrcImg = (NImage*)m_SrcImg;
	NImage* RefImg = (NImage*)m_RefImg;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Subtract(SrcImg, RefImg));
}

NIMGPROCESSDLL_API	bool __cdecl BitwiseXOR(LONG_PTR m_SrcImg, LONG_PTR m_RefImg, LONG_PTR m_ImgPro)
{
	NImage* SrcImg = (NImage*)m_SrcImg;
	NImage* RefImg = (NImage*)m_RefImg;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->BitwiseXOR(SrcImg, RefImg));
}

NIMGPROCESSDLL_API	bool __cdecl Inverse_SIMD(LONG_PTR m_Img, LONG_PTR m_ImgPro)
{

	NImage *Img = (NImage*)m_Img;
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Inverse_SIMD(Img));

}

NIMGPROCESSDLL_API	bool __cdecl SingleThresholding_SIMD(LONG_PTR m_Img, LONG_PTR m_ImgPro, int threshold)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->SingleThresholding_SIMD(Img, threshold));
}
