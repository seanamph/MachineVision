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


struct TAB 																	// 線段結構
{
	int  label, x1, x2, y, flag;
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
	struct TAB* tabs;

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
	int  Blob_Labelling();
	int Contour_Tracing();

#define  MAX_DOTN  100000
#define	 MAX_NUM   60000

	// Lab_12 Blob_Labelling from line 12 to line 20
	int   LineCoding(BYTE** list, int wid, int hei);		  						// 線段編碼

	void  SearchArea(struct TAB* tab, int num, int flag);  						// 以4/8相鄰方式搜索相連接區域(線段編碼步驟2, 3, 4)
	int   CreateLineTableIndex(struct TAB* tab, int num, int area[][2], int a_n);	// 建立連通區域資料索引表

	int   CreateTab(BYTE** list, int x, int y, int wid, int hei, struct TAB* tab);	// 建立線段表並初始化(線段編碼步驟1)
	int   MakeLabel(struct TAB* tab, int num, int data[][2], int flag);			// 對線段作標記(線段編碼步驟2)
	void  UniformLabel(struct TAB* tab, int num, int data[][2], int d_num);		// 統一線段編碼(線段編碼步驟3)
	void  SortLabel(struct TAB* tab, int num);									// 線段按標記排序(線段編碼步驟4)

	// Lab_12 Contour Tracing from line 23 to line 24
	int   SingleTrack(BYTE** list, int i, int j, int iop, int* code, int flag,
		int wid, int hei);											// 輪廓追蹤

	// Practice from line 27 to line 29
	void  CentreGravity(struct TAB* tab, int dot_n, double* px, double* py);		// 計算區域重心
	int   Perimeter(int* code); 												// 計算周長
	void  OutRectangle(int* code, int* x1, int* y1, int* x2, int* y2);				// 計算外接矩形

	int CalculateBlobArea();  //取得 Blob 面積的函式

};

#endif		//!_NIMAGE_H


#endif	