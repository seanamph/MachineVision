// NImageDLL.cpp : 定義 DLL 應用程式的匯出函式。
// Linux Version

#include "NImage.h"
#include "NImgProcess.h"
#include "NImgProcessDLL.h"


NIMGPROCESSDLL_API unsigned long CreateNImgProcess()
{
	return (unsigned long) new NImgProcess();
}


NIMGPROCESSDLL_API bool DestroyNImgProcess(unsigned long m_ImgPro)
{
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;
	
	if (ImgPro) delete ImgPro;

	return true;

}

NIMGPROCESSDLL_API	bool Inverse(unsigned long m_Img, unsigned long m_ImgPro)
{
	
	NImage *Img = (NImage*) m_Img;
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Inverse(Img));

}

NIMGPROCESSDLL_API	bool SingleThresholding(unsigned long m_Img, unsigned long m_ImgPro, int threshold)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->SingleThresholding(Img, threshold));
}

NIMGPROCESSDLL_API	bool OtsuThresholding(unsigned long m_Img, unsigned long m_Img2, unsigned long m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImage* Img2 = (NImage*)m_Img2;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->OtsuThresholding(Img, Img2));
}

NIMGPROCESSDLL_API	bool Sobel(unsigned long m_Img, unsigned long m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Sobel(Img));
}

NIMGPROCESSDLL_API	bool Laplacian(unsigned long m_Img, unsigned long m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Laplacian(Img));
}

NIMGPROCESSDLL_API	bool Mean(unsigned long m_Img, unsigned long m_ImgPro)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Mean(Img));
}

NIMGPROCESSDLL_API	bool Subtract(unsigned long m_SrcImg, unsigned long m_RefImg, unsigned long m_ImgPro)
{
	NImage* SrcImg = (NImage*)m_SrcImg;
	NImage* RefImg = (NImage*)m_RefImg;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Subtract(SrcImg, RefImg));
}

NIMGPROCESSDLL_API	bool BitwiseXOR(unsigned long m_SrcImg, unsigned long m_RefImg, unsigned long m_ImgPro)
{
	NImage* SrcImg = (NImage*)m_SrcImg;
	NImage* RefImg = (NImage*)m_RefImg;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->BitwiseXOR(SrcImg, RefImg));
}

NIMGPROCESSDLL_API	bool Dilation3x3(unsigned long m_Img, unsigned long m_Img2, unsigned long m_ImgPro)
{
	NImage*	Img = (NImage*)m_Img;
	NImage*	Img2 = (NImage*)m_Img2;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Dilation3x3(Img, Img2));
}

NIMGPROCESSDLL_API	bool Erosion3x3(unsigned long m_Img, unsigned long m_Img2, unsigned long m_ImgPro)
{
	NImage*	Img = (NImage*)m_Img;
	NImage*	Img2 = (NImage*)m_Img2;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Erosion3x3(Img, Img2));
}

NIMGPROCESSDLL_API	bool Small_Transform(unsigned long m_SrcImg, unsigned long m_OutImg, unsigned long m_ImgPro)
{
	NImage*	SrcImg = (NImage*)m_SrcImg;
	NImage*	OutImg = (NImage*)m_OutImg;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Small_Transform(SrcImg, OutImg));
}

NIMGPROCESSDLL_API	bool FromImageToVector(unsigned long m_Img, u_char *m_Vector, int element_num, unsigned long m_ImgPro)
{
	NImage*	Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->FromImageToVector(Img, m_Vector, element_num));
}

NIMGPROCESSDLL_API	bool Split_Image(unsigned long m_SrcImg, int start_x, int start_y, int split_wid,
									int split_hei, unsigned long m_SubImg, unsigned long m_ImgPro)
{
	NImage*	SrcImg = (NImage*)m_SrcImg;
	NImage*	SubImg = (NImage*)m_SubImg;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Split_Image(SrcImg, start_x, start_y, split_wid, split_hei, SubImg));
}

NIMGPROCESSDLL_API	bool Inverse_SIMD(unsigned long m_Img, unsigned long m_ImgPro)
{

	NImage *Img = (NImage*)m_Img;
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Inverse_SIMD(Img));

}

NIMGPROCESSDLL_API	bool SingleThresholding_SIMD(unsigned long m_Img, unsigned long m_ImgPro, int threshold)
{
	NImage* Img = (NImage*)m_Img;
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->SingleThresholding_SIMD(Img, threshold));
}
