// NImage.h: interface for the NImage class.
//
//////////////////////////////////////////////////////////////////////


#include <windows.h>
#include <vector>
#include <algorithm>


#ifndef		_NIMAGE_H
#define		_NIMAGE_H

#ifndef		_INC_PROCESSH
#define		_INC_PROCESSH

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

struct IMAGEPARAMENT
{
	int		nWidth;
	int		nHeight;
	int		nBitCount;
	int		nBytesPerLine;
	int		nBytesPerPixel;
	int		nNumColors;
	int		nSize;
};


class NImage 
{
private:
	HBITMAP			hBitmap;
 	LPBYTE    		lpBits;

	int				nWidth;
	int				nHeight;
	int				nBitCount;
    int				nBytesPerLine;
	int				nBytesPerPixel;
	int				nNumColors;
	int				nSize;

	HDC				hMemDC;


public:
	NImage();
 	~NImage();
public:

// Overrides
 	virtual BOOL  BitBlt(HDC,int,int,int,int,int,int,DWORD);
 	virtual BOOL  MaskBlt(HDC,int,int,HBITMAP,DWORD);
  	virtual HDC   GetDC();
	virtual void  ReleaseDC();

	void  Create(int Width,int Height,int Bits,DWORD dwFlags=0);
 	BOOL  IsNull();
	void  Destroy();

	int   GetWidth();
	int   GetHeight();
	int   GetBPP();
	__int64	  GetPitch();
	int	  GetMaxColorTableEntries();
  
	BYTE* GetPixelAddress(int x,int y);
	COLORREF GetPixel(int x,int y );
	void  GetColorTable(int m, int n, RGBQUAD* ColorTab);
	void  SetColorTable(int m, int n, RGBQUAD* ColorTab);

	BOOL  LoadBMP(char* filename);
	BOOL  SaveBMP(char* filename);

	HBITMAP* GetBitmap();


	// Mean filter (3x3)
	void MeanFilter3x3();

	// Sobel filter
	void SobelFilter();

	// Laplacian filter
	void LaplacianFilter();

	void ApplyConvolution(const std::vector<std::vector<__int64>>& kernel);



	void  Threshold();

	int   Otsu(long* pg);
	int   KSW_Entropic(long* pg);
	int   Moment(long* pg);

	void  histog(BYTE** list, long* pg, int x, int y, int Dx, int Dy);
	int   MaxMin(double* tab, int flag);
	int   Ptile(long* pg, double nn);


	void  GetImageParament( struct IMAGEPARAMENT* ppImgParam);

	BYTE** Create2DList();
	void  Release2DList(BYTE** list);



	void  AdaptiveMeanThreshold(int blockSize);
	void  AdaptiveGaussianThreshold(int blockSize);
};

#endif		//!_NIMAGE_H


#endif	