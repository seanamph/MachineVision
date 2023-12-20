#pragma once
#include <windows.h>
#include "NImage.h"

#ifndef		_NGAUGE_H
#define		_NGAUGE_H


class NGauge
{
private:
	BYTE** 	Create2DList(NImage* pImg);
	void  	Release2DList(BYTE** list);
	int		SubPixel_core(BYTE **list0, BYTE **MaskList,int wid, int hei, double *sub_x, double *sub_y);
public:
	NGauge();
	~NGauge();
public:
	int		SubPixel_EdgeDetector(NImage *pImg, NImage *pMaskImg, double *sub_x, double *sub_y);
	bool	CircleFitByKasa(double *edgelist_x, double *edgelist_y, int edge_num, double *result_x, 
							double *result_y, double *result_r);
};


#endif		//!_NGAUGE_H

