// Image.cpp: implementation of the NImage class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "NImage.h"
#include <vector>
#include <algorithm>

NImage::NImage()
{
	hBitmap=NULL;
	hMemDC=NULL;
}

NImage::~NImage()
{
	Destroy();
}

void NImage::Create(int Dx,int Dy,int Bits,DWORD dwFlags)
{
   BITMAPINFOHEADER BIH = {40,0,0,1,0,0,0,0,0,0,0  } ;
   LPBITMAPINFO	    lpBmi;
    
   nWidth = Dx;
   nHeight = Dy;
   nBitCount= Bits;
   nBytesPerLine = (nWidth*nBitCount+31)/32*4;
   nBytesPerPixel = nBitCount/8;
   if (nBitCount>8) nNumColors=0;
   else  nNumColors=1<<nBitCount;
   nSize=nBytesPerLine*nHeight;

   BIH.biWidth=nWidth;    
   BIH.biHeight=nHeight;	      
   BIH.biBitCount=nBitCount;
   
   lpBmi=(LPBITMAPINFO) malloc(40+4*nNumColors);
   memcpy(lpBmi,&BIH,40);
 
   hBitmap=CreateDIBSection(NULL,lpBmi,DIB_RGB_COLORS,
	                         (VOID**) &lpBits,NULL,0);
   free(lpBmi);
}

BOOL  NImage::IsNull()
{
	if (hBitmap==NULL)
		return(TRUE);
	else
		return(FALSE);
}


void  NImage::Destroy()
{
    if (hBitmap!=NULL) {
		DeleteObject(hBitmap);
   		hBitmap=NULL;
	}
}

BYTE* NImage::GetPixelAddress(int x,int y)
{
	return(lpBits+(nHeight-1-y)*nBytesPerLine+x*nBytesPerPixel);
}

COLORREF NImage::GetPixel(int x,int y)
{
	LPBYTE	lpBuf;
	DWORD	dwValue=0;
	RGBQUAD	ColorTab;

	lpBuf=(LPBYTE)lpBits+(nHeight-1-y)*nBytesPerLine+x*nBytesPerPixel;
	memcpy(&dwValue,lpBuf,nBytesPerPixel);
	if (nBitCount<=8) {
		GetColorTable(dwValue,1,&ColorTab);
		dwValue=RGB(ColorTab.rgbRed,
			    ColorTab.rgbGreen,ColorTab.rgbBlue);
	}
	else {
		dwValue=RGB((dwValue&0xff0000)>>16,
			    (dwValue&0xff00)>>8,dwValue&0xff);
	}
	return(dwValue);
}

int   NImage::GetWidth()
{
	return(nWidth);
}

int   NImage::GetHeight()
{
	return(nHeight);
}

int   NImage::GetBPP()
{
	return(nBitCount);
}

__int64	  NImage::GetPitch()
{
	return(GetPixelAddress(0,1)-GetPixelAddress(0,0));
} 

int	  NImage::GetMaxColorTableEntries()
{
	if (nNumColors>256) return(256);
	return(nNumColors);
}

void  NImage::GetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC		hMemDC;

    hMemDC =CreateCompatibleDC(NULL); 
    SelectObject(hMemDC,hBitmap);
 	GetDIBColorTable(hMemDC,m,n,ColorTab);
    DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

void  NImage::SetColorTable(int m, int n, RGBQUAD* ColorTab)
{
	HDC		hMemDC;

    hMemDC =CreateCompatibleDC(NULL); 
    SelectObject(hMemDC,hBitmap);
 	SetDIBColorTable(hMemDC,m,n,ColorTab);
    DeleteObject(hMemDC);
	DeleteDC(hMemDC);
}

HDC  NImage::GetDC()
{
   hMemDC =CreateCompatibleDC(NULL); 
   SelectObject(hMemDC,hBitmap);
   return hMemDC;
}

void NImage::ReleaseDC()
{
   if (hMemDC) {
      DeleteObject(hMemDC);
	  DeleteDC(hMemDC);
   }
}

BOOL  NImage::BitBlt(HDC hDestDC,int xDest,int yDest,
                     int nDestWidth,int nDestHeight,
					 int xSrc,int ySrc,DWORD dwROP) 
{
	HDC		hSrcDC;

	hSrcDC=GetDC();
	SelectObject(hSrcDC,hBitmap);
	::BitBlt(hDestDC,xDest,yDest,nDestWidth,nDestHeight,
		          hSrcDC,xSrc,ySrc,dwROP);
 	ReleaseDC();
   	return(TRUE);
}

BOOL  NImage::MaskBlt(HDC hDestDC,int xDest,int yDest,
			  HBITMAP hBitmap,DWORD dwROP)
{
	HDC		hDC=NULL,hSrcDC;

    hSrcDC = CreateCompatibleDC(hDC); 
    SelectObject(hSrcDC,hBitmap); 
	::BitBlt(hDestDC,xDest,yDest,nWidth,nHeight,
	          hSrcDC,xDest,yDest,dwROP);
    DeleteDC(hSrcDC); 
   	return(TRUE);
}

//--------------------------------------------------------------
//  BMP

BOOL NImage::LoadBMP(char* filename)
{
	BITMAPFILEHEADER BFH;
    BITMAPINFOHEADER BIH;
	RGBQUAD  ColorTab[256];
    FILE	*fp;
        
	fopen_s(&fp, filename,"rb");
	if (fp==NULL)
		return(FALSE);

    fread(&BFH,sizeof(BITMAPFILEHEADER),1,fp);
    fread(&BIH,sizeof(BITMAPINFOHEADER),1,fp);

	if ((BFH.bfType!='MB')||(BIH.biCompression !=0)) {
		fclose(fp);   
 		return(FALSE);
	}
 
	Create(BIH.biWidth,BIH.biHeight,BIH.biBitCount,0);

    if (nNumColors>0) {
 		fread(ColorTab,4,nNumColors,fp);
		SetColorTable(0,nNumColors,ColorTab);
	}

	fseek(fp,BFH.bfOffBits,SEEK_SET);
    fread(lpBits,nSize,1,fp);
	fclose(fp);   
   	return(TRUE);
}

BOOL NImage::SaveBMP(char* filename)
{
	BITMAPFILEHEADER BFH={'MB',0,0,0,0};
    BITMAPINFOHEADER Bmih={40,1,1,1,8,0,0,0,0,0,0};
	RGBQUAD	ColorTab[256];
	DWORD	dwBmiSize;
 	FILE	*fp;
      
    dwBmiSize=40+4*nNumColors;

	fopen_s(&fp, filename,"w+b");
	if (fp==NULL)
		return(FALSE);

	BFH.bfSize   =sizeof(BITMAPFILEHEADER)+dwBmiSize+nSize;
	BFH.bfOffBits=sizeof(BITMAPFILEHEADER)+
		sizeof(BITMAPINFOHEADER)+nNumColors*sizeof(RGBQUAD);

	Bmih.biWidth = nWidth;
	Bmih.biHeight = nHeight;
	Bmih.biBitCount = nBitCount;

    fwrite(&BFH,1,sizeof(BITMAPFILEHEADER),fp);
    fwrite((BYTE*)&Bmih,1,40,fp);
	if (nBitCount<=8) {
		GetColorTable(0,nNumColors,ColorTab);
		fwrite(ColorTab,4,nNumColors,fp);
	}
    fwrite(lpBits,1,nSize,fp);
	fclose(fp);
   	return(TRUE);
}
//  BMP

HBITMAP* NImage::GetBitmap()
{
    return(&hBitmap);
}

void NImage::MeanFilter3x3()
{
	ApplyConvolution({
	   {1, 1, 1},
	   {1, 1, 1},
	   {1, 1, 1}
		});
}

void NImage::SobelFilter()
{
	ApplyConvolution({
	   {-1, 0, 1},
	   {-2, 0, 2},
	   {-1, 0, 1}
		});
}

void NImage::LaplacianFilter()
{
	ApplyConvolution({
	  { 0,  1, 0},
	  { 1, -4, 1},
	  { 0,  1, 0}
		});
}

void NImage::ApplyConvolution(const std::vector<std::vector<__int64>>& kernel)
{
	int kSize = kernel.size();  // Assuming the kernel is a square
	int kHalfSize = kSize / 2;
	BYTE* newPixels = new BYTE[nSize];

	for (int y = 0; y < nHeight; ++y)
	{
		for (int x = 0; x < nWidth; ++x)
		{
			int sum = 0;
			for (int ky = -kHalfSize; ky <= kHalfSize; ++ky)
			{
				for (int kx = -kHalfSize; kx <= kHalfSize; ++kx)
				{
					int nx = x + kx;
					int ny = y + ky;
					if (nx >= 0 && nx < nWidth && ny >= 0 && ny < nHeight)
					{
						sum += lpBits[ny * nBytesPerLine + nx] * kernel[ky + kHalfSize][kx + kHalfSize];
					}
				}
			}
			newPixels[y * nBytesPerLine + x] = static_cast<BYTE>((std::max)(0, (std::min)(255, sum)));

		}
	}

	memcpy(lpBits, newPixels, nSize);
	delete[] newPixels;
}


void NImage::GetImageParament( struct IMAGEPARAMENT* ppImgParam)
{

	ppImgParam->nWidth = GetWidth();
	ppImgParam->nHeight = GetHeight();
	ppImgParam->nBitCount = GetBPP();
	ppImgParam->nBytesPerLine = (GetWidth() * GetBPP() + 31) / 32 * 4;
	ppImgParam->nBytesPerPixel = GetBPP() / 8;

	if (GetBPP() <= 8)
		ppImgParam->nNumColors = 1 << GetBPP();
	else
		ppImgParam->nNumColors = 0;

	ppImgParam->nSize = ppImgParam->nBytesPerLine * ppImgParam->nHeight;
}


BYTE** NImage::Create2DList()
{
	struct		IMAGEPARAMENT P;
	int			i;
	BYTE** list;

	GetImageParament( &P);
	list = (BYTE**)malloc(P.nHeight * sizeof(BYTE*));
	for (i = 0;i < P.nHeight;i++)
		list[i] = (BYTE*)GetPixelAddress(0, i);

	return(list);
}

void NImage::Release2DList(BYTE** list)
{
	free(list);
}


void NImage::Threshold()
{
	struct	IMAGEPARAMENT P;
	BYTE** list, * lpBuf;
	long	pg[256];
	int		x, y, thre;

	GetImageParament( &P);

	list = (BYTE**)Create2DList();
	histog(list, pg, 0, 0, P.nWidth, P.nHeight);

	thre = Otsu(pg);

	for (y = 0;y < P.nHeight;y++)
	{
		lpBuf = (BYTE*)GetPixelAddress(0, y);
		for (x = 0;x < P.nWidth;x++, lpBuf++)
		{
			if (*lpBuf >= thre) *lpBuf = 255;
			else		        *lpBuf = 0;
		}
	}

	Release2DList(list);
}


int NImage::Otsu(long* pg)
{
	int  i, j, p;
	double m0, m1, M0, M1, u, v, w[256];

	M0 = M1 = 0;
	for (i = 0;i < 256;i++)
	{
		M0 += pg[i];     M1 += pg[i] * i;
	}

	for (j = 0;j < 256;j++)
	{
		m0 = m1 = 0;
		for (i = 0;i <= j;i++)
		{
			m0 += pg[i];
			m1 += pg[i] * i;
		}

		if (m0) u = m1 / m0;
		else   u = 0;

		if (M0 - m0) v = (M1 - m1) / (M0 - m0);
		else      v = 0;

		w[j] = m0 * (M0 - m0) * (u - v) * (u - v);
	}

	p = MaxMin(w, 1);
	return(p);
}


int NImage::KSW_Entropic(long* pg)
{
	long   i, t, s;
	double p[256], Pt[256], Ht[256], HT, H[256];
	double A, B, C;

	for (i = 0, s = 0;i < 256;i++) s += pg[i];
	for (i = 0;i < 256;i++) p[i] = ((double)pg[i]) / s;

	Pt[0] = p[0];
	for (i = 1;i < 256;i++) Pt[i] = Pt[i - 1] + p[i];

	for (i = 0;i < 256;i++)
	{
		if (p[i] == 0) Ht[i] = 0;
		else  Ht[i] = -p[i] * log(p[i]);
	}
	for (i = 1;i < 256;i++) Ht[i] += Ht[i - 1];

	HT = Ht[255];
	for (i = 0;i < 256;i++)
	{
		A = Pt[i] * (1 - Pt[i]);
		if (A > 0) A = log(A);

		B = Pt[i];
		if (B > 0) B = Ht[i] / B;

		C = 1 - Pt[i];
		if (C > 0) C = (HT - Ht[i]) / C;

		H[i] = A + B + C;
	}

	t = MaxMin(H, 1);
	return(t);
}

int NImage::Moment(long* pg)
{
	long   i, t;
	double m0, m1, m2, m3, p0, C0, C1;

	m0 = m1 = m2 = m3 = 0;
	for (i = 0;i < 256;i++)
	{
		m0 += (double)pg[i];
		m1 += (double)pg[i] * i;
		m2 += (double)pg[i] * i * i;
		m3 += (double)pg[i] * i * i * i;
	}

	C0 = (m1 * m3 - m2 * m2) / (m0 * m2 - m1 * m1);
	C1 = (m1 * m2 - m0 * m3) / (m0 * m2 - m1 * m1);
	p0 = 0.5 - (m1 / m0 + C1 / 2) / sqrt(C1 * C1 - 4 * C0);
	t = Ptile(pg, p0);

	return(t);
}


void NImage::histog(BYTE** list, long* pg, int x, int y, int Dx, int Dy)
{
	int   i, j;

	for (i = 0;i < 256;i++)  pg[i] = 0;

	for (i = y;i < y + Dy;i++)
		for (j = x;j < x + Dx;j++)
			pg[list[i][j]]++;
}

int  NImage::MaxMin(double* tab, int flag)
{
	double  max, min;
	int     i, p, q;

	max = min = tab[128];
	p = q = 128;

	for (i = 0;i < 256;i++)
	{

		if (tab[i] > max)
		{
			max = tab[i];
			p = i;
		}

		if (tab[i] < min)
		{
			min = tab[i];
			q = i;
		}
	}

	if (flag == 1)
	{
		for (i = 0;i < 256;i++)
			tab[i] = 120 * (max - tab[i]) / (max - min);
	}
	else
	{
		for (i = 0;i < 256;i++)
			tab[i] = 120 * (tab[i] - min) / (max - min);

		p = q;
	}

	return(p);
}

int NImage::Ptile(long* pg, double nn)
{
	int  i;
	double mm, kk;

	for (i = 0, mm = 0;i < 256;i++) mm += pg[i];

	kk = 0;
	for (i = 0;i < 256;i++)
	{
		kk += (double)pg[i] / mm;
		if (kk >= nn)  break;
	}
	return i;
}


void NImage::AdaptiveMeanThreshold(int blockSize)
{
	struct IMAGEPARAMENT P;
	BYTE** list, * lpBuf;
	int localMean;
	int halfBlockSize = blockSize / 2;

	GetImageParament(&P);
	list = (BYTE**)Create2DList();

	for (int y = 0; y < P.nHeight; y++)
	{
		for (int x = 0; x < P.nWidth; x++)
		{
			int sum = 0, count = 0;
			for (int dy = -halfBlockSize; dy <= halfBlockSize; dy++)
			{
				for (int dx = -halfBlockSize; dx <= halfBlockSize; dx++)
				{
					if (x + dx >= 0 && x + dx < P.nWidth && y + dy >= 0 && y + dy < P.nHeight)
					{
						lpBuf = (BYTE*)GetPixelAddress(x + dx, y + dy);
						sum += *lpBuf;
						count++;
					}
				}
			}
			localMean = sum / count;

			lpBuf = (BYTE*)GetPixelAddress(x, y);
			*lpBuf = (*lpBuf > localMean) ? 255 : 0;
		}
	}

	Release2DList(list);
}


void NImage::AdaptiveGaussianThreshold(int blockSize)
{
	struct IMAGEPARAMENT P;
	BYTE** list, * lpBuf;
	int localMean;
	int halfBlockSize = blockSize / 2;

	GetImageParament(&P);
	list = (BYTE**)Create2DList();

	for (int y = 0; y < P.nHeight; y++)
	{
		for (int x = 0; x < P.nWidth; x++)
		{
			double weightedSum = 0, weightSum = 0;
			for (int dy = -halfBlockSize; dy <= halfBlockSize; dy++)
			{
				for (int dx = -halfBlockSize; dx <= halfBlockSize; dx++)
				{
					if (x + dx >= 0 && x + dx < P.nWidth && y + dy >= 0 && y + dy < P.nHeight)
					{
						double distanceSquared = dx * dx + dy * dy;
						double weight = exp(-distanceSquared / (2.0 * blockSize * blockSize));  // 基於高斯函數
						lpBuf = (BYTE*)GetPixelAddress(x + dx, y + dy);
						weightedSum += weight * (*lpBuf);
						weightSum += weight;
					}
				}
			}
			double localGaussianMean = weightedSum / weightSum;

			lpBuf = (BYTE*)GetPixelAddress(x, y);
			*lpBuf = (*lpBuf > localGaussianMean) ? 255 : 0;
		}
	}

	Release2DList(list);
}
