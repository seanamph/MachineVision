// NGaugeDLL.cpp : �w�q DLL ���ε{�����ץX�禡�C
//
#include "NGaugeDLL.h"
#include "NImage.h"
#include "NGauge.h"

// �o�O�ץX�禡���d�ҡC
NGAUGEDLL_API LONG_PTR __cdecl CreateNGauge()
{
	return (LONG_PTR) new NGauge();
}

NGAUGEDLL_API  bool	__cdecl DestroyNGauge(LONG_PTR m_Gauge)
{
	NGauge *Gauge = (NGauge*)m_Gauge;

	if (Gauge) delete Gauge;

	return true;
}

NGAUGEDLL_API  int  __cdecl SubPixel_EdgeDetector(LONG_PTR m_Img, LONG_PTR m_MaskImg, LONG_PTR m_Gauge, double *sub_x, double *sub_y)
{
	NImage *Img = (NImage*)m_Img;
	NImage *MaskImg = (NImage*)m_MaskImg;
	NGauge *Gauge = (NGauge*)m_Gauge;



	return Gauge->SubPixel_EdgeDetector(Img, MaskImg, sub_x, sub_y);
}

NGAUGEDLL_API  bool	__cdecl CircleFitByKasa(LONG_PTR m_Gauge, double *edgelist_x, double *edgelist_y, int edge_num,
											double *result_x, double *result_y, double *result_r)
{
	NGauge *Gauge = (NGauge*)m_Gauge;

	return Gauge->CircleFitByKasa(edgelist_x, edgelist_y, edge_num, result_x, result_y, result_r);
}



