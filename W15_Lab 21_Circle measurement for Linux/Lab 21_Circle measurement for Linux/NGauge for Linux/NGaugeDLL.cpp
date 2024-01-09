// NGaugeDLL.cpp : 定義 DLL 應用程式的匯出函式。
// Linux Version

#include "NImage.h"
#include "NGauge.h"
#include "NGaugeDLL.h"

// 這是匯出函式的範例。
NGAUGEDLL_API unsigned long CreateNGauge()
{
	return (unsigned long) new NGauge();
}

NGAUGEDLL_API  bool	DestroyNGauge(unsigned long m_Gauge)
{
	NGauge *Gauge = (NGauge*)m_Gauge;

	if (Gauge) delete Gauge;

	return true;
}

NGAUGEDLL_API  int  SubPixel_EdgeDetector(unsigned long m_Img, unsigned long m_MaskImg, unsigned long m_Gauge, double *sub_x, double *sub_y)
{
	NImage *Img = (NImage*)m_Img;
	NImage *MaskImg = (NImage*)m_MaskImg;
	NGauge *Gauge = (NGauge*)m_Gauge;

	return Gauge->SubPixel_EdgeDetector(Img, MaskImg, sub_x, sub_y);
}

NGAUGEDLL_API  bool	CircleFitByKasa(unsigned long m_Gauge, double *edgelist_x, double *edgelist_y, int edge_num,
									double *result_x, double *result_y, double *result_r)
{
	NGauge *Gauge = (NGauge*)m_Gauge;

	return Gauge->CircleFitByKasa(edgelist_x, edgelist_y, edge_num, result_x, result_y, result_r);
}



