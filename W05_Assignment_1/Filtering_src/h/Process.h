#pragma once

#ifndef		_INC_PROCESSH
#define		_INC_PROCESSH

void  Sobel(NImage *pImg)

void  Sobel_core(BYTE **list0, BYTE **list1, int Dx, int Dy);
void  Laplacian_core(BYTE **list0, BYTE **list1, int Dx, int Dy);
void  Mean_core(BYTE **list0, BYTE **list1, int Dx, int Dy);

void  ArrayCopy(BYTE **list0,BYTE **list1,int Dx,int Dy);

#endif  //!_INC_PROCESSH


 