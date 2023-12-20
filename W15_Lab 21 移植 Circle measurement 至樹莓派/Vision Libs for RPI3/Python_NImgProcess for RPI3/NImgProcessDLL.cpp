// NImageDLL.cpp for Linux
//
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

NIMGPROCESSDLL_API	bool Inverse(unsigned long m_ImgPro, u_char *m_Img, int wid, int hei)
{
	NImgProcess *ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->Inverse(m_Img, wid, hei));

}

NIMGPROCESSDLL_API	bool SingleThresholding(unsigned long m_ImgPro, u_char *m_Img, int wid, int hei, int threshold)
{
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->SingleThresholding(m_Img, wid, hei, threshold));
}

NIMGPROCESSDLL_API	bool OtsuThresholding(unsigned long m_ImgPro, u_char *m_Img, int wid, int hei)
{
	NImgProcess* ImgPro = (NImgProcess*)m_ImgPro;

	return (ImgPro->OtsuThresholding(m_Img, wid, hei));
}
