#pragma once

#ifdef NGAUGEDLL_EXPORTS
#define NGAUGEDLL_API __attribute__ ((visibility ("default")))
#else
#define NGAUGEDLL_API __attribute__ ((visibility ("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

	NGAUGEDLL_API  unsigned long CreateNGauge();
	NGAUGEDLL_API  bool	DestroyNGauge(unsigned long m_Gauge);
	NGAUGEDLL_API  int  SubPixel_EdgeDetector(unsigned long m_Img, unsigned long m_MaskImg, unsigned long m_Gauge, double *sub_x, double *sub_y);
	NGAUGEDLL_API  bool	CircleFitByKasa(unsigned long m_Gauge, double *edgelist_x, double *edgelist_y, int edge_num, 
										double *result_x,double *result_y, double *result_r);
#ifdef __cplusplus
}
#endif


