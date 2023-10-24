// NImage.h: interface for the NImage class.
//
//////////////////////////////////////////////////////////////////////


#include <windows.h>

#ifndef		_NIMAGE_H
#define		_NIMAGE_H

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

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
	int	  GetPitch();
	int	  GetMaxColorTableEntries();
  
	BYTE* GetPixelAddress(int x,int y);
	COLORREF GetPixel(int x,int y );
	void  GetColorTable(int m, int n, RGBQUAD* ColorTab);
	void  SetColorTable(int m, int n, RGBQUAD* ColorTab);

	BOOL  LoadBMP(char* filename);
	BOOL  SaveBMP(char* filename);

	HBITMAP* GetBitmap();

};

#endif		//!_NIMAGE_H

