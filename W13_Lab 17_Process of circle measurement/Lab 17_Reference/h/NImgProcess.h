// NImgProcess.h: interface for the NImage Process class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <windows.h>

#ifndef		_NIMGPROCESS_H
#define		_NIMGPROCESS_H


class NImgProcess
{
private:
//member variables
	int		nWidth;
	int		nHeight;
	int		nBitCount;
    int		nBytesPerLine;
	int		nBytesPerPixel;
	int		nNumColors;
	int		nSize;

private:
//member functions
	void  	GetImageParament(NImage* pImg);

	BYTE** 	Create2DList(NImage* pImg);
	void  	Release2DList(BYTE** list);
	void    ArrayCopy(BYTE **list0, BYTE **list1, int Dx, int Dy);
	
	void  	histog(BYTE** list,long* pg,int x, int y, int Dx, int Dy); 
	void    Sobel_core(BYTE **list0, BYTE **list1, int Dx, int Dy);
	void	Laplacian_core(BYTE **list0, BYTE **list1, int Dx, int Dy);
	void	Mean_core(BYTE **list0, BYTE **list1, int Dx, int Dy);
	int   	Otsu(long* pg);  	
	int   	MaxMin(double* tab,int flag);
	int   	Ptile(long* pg,double nn); 

public:
	NImgProcess();
 	~NImgProcess();
public:
//member functions
	bool	Inverse(NImage *pImg);
	bool	SingleThresholding(NImage *pImg, int threshold);
	bool	OtsuThresholding(NImage *pImg, NImage *pImg2);

	bool	Sobel(NImage *pImg);
	bool	Laplacian(NImage *pImg);
	bool	Mean(NImage *pImg);

	bool	Subtract(NImage *pSrcImg, NImage *pRefImg);
	bool	BitwiseXOR(NImage *pSrcImg, NImage *pRefImg);

	bool	Inverse_SIMD(NImage *pImg);
	bool	SingleThresholding_SIMD(NImage *pImg, int threshold);

	bool	Dilation3x3(NImage *pImg, NImage *pImg2);
	bool	Erosion3x3(NImage *pImg, NImage *pImg2);
};

#endif		//!_NImgProcess_H