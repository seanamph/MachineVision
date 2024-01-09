#pragma once

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "NImage.h"

#ifndef		_NGAUGE_H
#define		_NGAUGE_H


class NGauge
{
private:
	u_char** 	Create2DList(NImage* pImg);
	void  		Release2DList(u_char** list);
	int			SubPixel_core(u_char **list0, u_char **MaskList,int wid, int hei, double *sub_x, double *sub_y);
public:
	NGauge();
	~NGauge();
public:
	int			SubPixel_EdgeDetector(NImage *pImg, NImage *pMaskImg, double *sub_x, double *sub_y);
	bool		CircleFitByKasa(double *edgelist_x, double *edgelist_y, int edge_num, double *result_x, 
								double *result_y, double *result_r);
};


#endif		//!_NGAUGE_H

