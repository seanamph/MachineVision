#pragma once
#include <windows.h>

#ifdef NGAUGEDLL_EXPORTS
#define NGAUGEDLL_API __declspec(dllexport)
#else
#define NIMGPROCESSDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	NGAUGEDLL_API  LONG_PTR __cdecl CreateNGauge();
	NGAUGEDLL_API  bool	__cdecl DestroyNGauge(LONG_PTR m_Gauge);
	NGAUGEDLL_API  int  __cdecl SubPixel_EdgeDetector(LONG_PTR m_Img, LONG_PTR m_MaskImg, LONG_PTR m_Gauge, double *sub_x, double *sub_y);
	NGAUGEDLL_API  bool	__cdecl CircleFitByKasa(LONG_PTR m_Gauge, double *edgelist_x, double *edgelist_y, int edge_num, 
												double *result_x,double *result_y, double *result_r);
#ifdef __cplusplus
}
#endif


