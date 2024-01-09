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

	tabs = (struct TAB*)malloc(sizeof(struct TAB) * MAX_DOTN);
}


NImage::NImage(int Width, int Height)
{
	if (hBitmap != NULL)
	{
		DeleteObject(hBitmap);
		DeleteObject(hMemDC);
	}
	
	
	hBitmap = NULL;
	hMemDC = NULL;

	lpBits = 0;
	nSize = 0;
	nBitCount = 8;

	RGBQUAD  ColorTab[256];

	Create(Width, Height, 8, 0);

	if (nNumColors == 256)
	{
		for (int Index = 0; Index < 256; Index++)
		{
			ColorTab[Index].rgbBlue = Index;
			ColorTab[Index].rgbGreen = Index;
			ColorTab[Index].rgbRed = Index;
			ColorTab[Index].rgbReserved = 0;
		}

		SetColorTable(0, nNumColors, ColorTab);
	}
}
NImage::~NImage()
{
	free(tabs);
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
						double weight = exp(-distanceSquared / (2.0 * blockSize * blockSize));  // ��󰪴����
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





int NImage::Blob_Labelling()
{
	struct IMAGEPARAMENT P;
	BYTE** list, * lpBuf;
	int localMean;

	GetImageParament(&P);
	list = (BYTE**)Create2DList();
	int result = NImage::LineCoding(list, P.nWidth, P.nHeight);


	for (int y = 0; y < P.nHeight; y++)
	{
		for (int x = 0; x < P.nWidth; x++)
		{
			lpBuf = (BYTE*)GetPixelAddress(x, y);
			*lpBuf =  255;
		}
	}
	for (int i = 0; i < result; ++i) {
		double px = 0;
		double py = 0;
		NImage::CentreGravity(tabs, i, &px, &py);
		for (int x = px - 5; x >= 0 && x <= P.nWidth &&  x < px + 5; ++x) {
			for (int y = py - 5;y >= 0 && y <= P.nHeight && y < py + 5; ++y) {
				lpBuf = (BYTE*)GetPixelAddress(x, y);
				*lpBuf = 0;
			}
		}
	}


	Release2DList(list);
	return result;
}




int NImage::Contour_Tracing()
{
	int i = 0;   
	int j = 0;  
	int iop = 0; 
	int flag = 0; 
	int code[MAX_DOTN]; 
	struct IMAGEPARAMENT P;
	BYTE** list, * lpBuf;
	int localMean;

	GetImageParament(&P);
	list = (BYTE**)Create2DList();
	int result = NImage::SingleTrack(list, i, j, iop, code, flag, P.nWidth, P.nHeight);


	for (int y = 0; y < P.nHeight; y++)
	{
		for (int x = 0; x < P.nWidth; x++)
		{
			lpBuf = (BYTE*)GetPixelAddress(x, y);
			*lpBuf = 255;
		}
	}
	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
					 {-1, 0},{-1,+1},{ 0,+1},{+1,+1} };					// ��X���F�I�P�����I�����Юt�Ȫ�
	for (int i = 0; i < result; ++i) {
		if(code[2] > -1) list[code[0]][code[1]] = 0;
	}
	int x = 0; 
	int y = 0;
	for (int k = 4; k < code[2] + 3; ++k) {
		int direction = code[k];
		 x += inc[direction][0];
		 y += inc[direction][1];

		lpBuf = (BYTE*)GetPixelAddress(x, y);
		*lpBuf = 0;
	}
	Release2DList(list);
	return result;
}

int NImage::LineCoding(BYTE** list, int wid, int hei)
{
	int		area[1000][2];
	int		num, an;


	num = CreateTab(list, 0, 0, wid, hei, tabs);
	SearchArea(tabs, num, 8);

	an = CreateLineTableIndex(tabs, num, area, 1000);

	 

	return an;
}

void NImage::SearchArea(struct TAB* tab, int num, int flag)
{
	int  data[1000][2], d_num;

	d_num = MakeLabel(tab, num, data, flag);
	UniformLabel(tab, num, data, d_num);
	SortLabel(tab, num);
}

int NImage::CreateLineTableIndex(struct TAB* tab, int num, int area[][2], int a_n)
{
	int		i, j, k, m, t;

	for (i = 0; i < a_n; i++) area[i][0] = num;
	j = tab[0].label;
	k = m = t = 0;

	for (i = 0;i <= num;i++)
	{
		if (tab[i].label != j)
		{
			area[k][0] = m;
			area[k][1] = t;
			j = tab[i].label;
			k++;
			m = i;
			t = 0;
		}

		t += tab[i].x2 - tab[i].x1 + 1;
		if (k == a_n - 1) break;
	}

	return(k);
}

int NImage::CreateTab(BYTE** list, int x, int y, int wid, int hei, struct TAB* tab)
{
	int   i, j, k, f, num;

	for (i = y, num = 0;i < y + hei;i++)
	{
		for (j = x, k = 0, f = 0;j < x + wid;j++)
		{
			if (list[i][j]) k++;
			else if (k) f = 1;

			if ((j == x + wid - 1) && (k > 0))
			{
				j++;
				f = 1;
			}

			if (f == 1)
			{
				tab[num].label = 0;
				tab[num].x1 = j - k;
				tab[num].y = i;
				tab[num].x2 = j - 1;
				num++;
				f = k = 0;
			}
		}
	}

	return(num);
}

int NImage::MakeLabel(struct TAB* tab, int num, int data[][2], int flag)
{
	int  line[1000];
	int  i, j, k0, k1, k2, t, no, d_num;
	int  m, n, x1l, x1r, x2l, x2r, y, end, color;

	if (flag == 8) no = 1;
	else  no = 0;

	tab[num].y = 0;
	y = -1;
	for (i = 0, end = 0;i <= num;i++)
	{
		if (tab[i].y != y)
		{
			line[end++] = i;
			y = tab[i].y;
		}
	}

	color = 1;
	k0 = k1 = line[0];
	d_num = 0;

	for (t = 0;t < end;t++)
	{
		k2 = line[t];
		for (i = k0;i < k1;i++)
		{
			y = tab[i].y;		m = tab[i].label;
			x1l = tab[i].x1;	x1r = tab[i].x2;
			for (j = k1;j < k2;j++)
			{
				if (tab[j].y != y + 1) break;
				n = tab[j].label;
				x2l = tab[j].x1;	x2r = tab[j].x2;

				if ((x1l <= x2r + no) && (x2l <= x1r + no))
				{
					if (m == n) continue;
					if (n == 0)
					{
						n = tab[j].label = m;
					}
					else
					{
						if (n < m)
						{
							data[d_num][0] = n;
							data[d_num][1] = m;
						}
						else
						{
							data[d_num][0] = m;
							data[d_num][1] = n;
						}

						d_num++;
					}
				}
			}
		}

		for (j = k1;j < k2;j++)
		{
			if (tab[j].label == 0)
				tab[j].label = color++;
		}

		k0 = k1;
		k1 = k2;
	}

	return(d_num);
}

void NImage::UniformLabel(struct TAB* tab, int num, int data[][2], int d_num)
{
	int  i, j, k, m, n;

	for (i = 0;i < d_num - 1;i++)
	{
		k = i;
		n = data[i][0];

		for (j = i + 1;j < d_num;j++)
		{
			if (data[j][0] < n)
			{
				k = j;
				n = data[j][0];
			}
		}

		m = data[i][0];            n = data[i][1];
		data[i][0] = data[k][0];   data[i][1] = data[k][1];
		data[k][0] = m;            data[k][1] = n;
	}

	for (i = d_num - 1;i >= 0;i--)
	{
		m = data[i][0];
		n = data[i][1];

		for (j = 0;j < num;j++)
		{
			if (tab[j].label == n)
				tab[j].label = m;
		}

		for (j = 0;j < i;j++)
		{
			if (data[j][0] == n)  data[j][0] = m;
			if (data[j][1] == n)  data[j][1] = m;
		}
	}
}

void NImage::SortLabel(struct TAB* tab, int num)
{
	int  i, j, k, n;
	struct TAB temp;

	for (i = 0;i < num - 1;i++)
	{
		k = i;
		n = tab[i].label;

		for (j = i + 1;j < num;j++)
		{
			if (tab[j].label < n)
			{
				k = j;
				n = tab[j].label;
			}
		}

		if (i != k)
		{
			memcpy(&temp, &tab[i], sizeof(struct TAB));
			memcpy(&tab[i], &tab[k], sizeof(struct TAB));
			memcpy(&tab[k], &temp, sizeof(struct TAB));
		}
	}
}

int NImage::SingleTrack(BYTE** list, int i, int j, int iop, int* code, int flag, int wid, int hei)
{
	int  kw, code_n;
	int  curr[2], next[2];
	int  n, n1, u, ki, kj, ns, ne;

	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
					 {-1, 0},{-1,+1},{ 0,+1},{+1,+1} };					// ��X���F�I�P�����I�����Юt�Ȫ�

	if (flag == 4) u = 2;
	else         u = 1;

	code[0] = curr[0] = next[0] = i;
	code[1] = curr[1] = next[1] = j;
	code_n = 3;
	code[3] = -1;

	do
	{
		kw = 0;
		ns = iop;    ne = ns - 8;

		for (n = ns;n > ne;n -= u)
		{
			n1 = (n + 8) % 8;
			ki = curr[0] + inc[n1][0];
			kj = curr[1] + inc[n1][1];

			if (ki < wid && ki >= 0 && kj < hei && kj >= 0)
			{
				if (list[kj][ki] > 0) 										// �i�b���]�w�֭�
					break;
			}
		}

		if (n != ne)
		{
			next[0] = ki;
			next[1] = kj;
			iop = n1;
		}
		else  kw = 1;

		if ((curr[0] == i) && (curr[1] == j) && (iop == code[3]))  break;

		code[code_n++] = iop;
		curr[0] = next[0];
		curr[1] = next[1];

		if ((flag == 8) && (iop % 2 == 0)) iop--;

		iop = (iop + 2) % 8;

	} while (kw == 0);

	code[2] = code_n - 3;

	return(code_n - 3);
}


void NImage::CentreGravity(struct TAB* tab, int tab_n, double* px, double* py)
{
	int    i;
	double len, xyu, yyu, sss;

	xyu = yyu = sss = 0;

	for (i = 0;i < tab_n;i++)
	{
		len = (tab[i].x2 - tab[i].x1 + 1);
		sss += len;
		xyu += len * (tab[i].x2 + tab[i].x1) / 2;
		yyu += len * tab[i].y;
	}

	xyu = xyu / sss;
	yyu = yyu / sss;

	*px = xyu;
	*py = yyu;
}


int NImage::Perimeter(int* code)
{
	int i, e = 0, ppp = 0, n;

	n = code[2];

	for (i = 3;i < n + 3;i++)
	{
		if (code[i] % 2) e++;
		else  ppp++;
	}

	ppp = (int)(ppp + (1.414 * e + 0.5));

	return(ppp);
}

void NImage::OutRectangle(int* code, int* x1, int* y1, int* x2, int* y2)
{
	int  i, n, k, x, y, xi, yi, xa, ya;
	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
					 {-1, 0},{-1,+1},{ 0,+1},{+1,+1} };					// ��X���F�I�P�����I�����Юt�Ȫ�

	n = code[2];
	xi = xa = x = code[0];
	yi = ya = y = code[1];

	for (i = 0;i < n;i++)
	{
		k = code[3 + i];
		x += inc[k][0];
		y += inc[k][1];

		if (x < xi) xi = x;
		if (x > xa) xa = x;
		if (y < yi) yi = y;
		if (y > ya) ya = y;
	}

	*x1 = xi;		*y1 = yi;
	*x2 = xa;		*y2 = ya;
}

int NImage::CalculateBlobArea()
{
	struct IMAGEPARAMENT P;
	BYTE** list, * lpBuf;
	int localMean;

	GetImageParament(&P);
	list = (BYTE**)Create2DList();
	int result = NImage::LineCoding(list, P.nWidth, P.nHeight);

	Release2DList(list);
	int area = 0;
	for (int i = 0; i < result; ++i) {
		TAB tab = tabs[i]; 
		for (int x = tab.x1; x <= tab.x2; ++x) {
			area++;
		}
	}
	return area;
}





