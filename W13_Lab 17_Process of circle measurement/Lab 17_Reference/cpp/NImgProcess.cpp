// NImgProcess.cpp: implementation of the NImage Process class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
//#include <emmintrin.h>		// for SSE2
//#include <tmmintrin.h>		// for SSSE3
#include <immintrin.h>


#include "NImage.h"
#include "NImgProcess.h"

NImgProcess::NImgProcess()
{
	nWidth = 0;
	nHeight = 0;
	nBitCount = 0;
    nBytesPerLine = 0;
	nBytesPerPixel = 0;
	nNumColors = 0;
	nSize = 0;
}

NImgProcess::~NImgProcess()
{
	
}

bool NImgProcess::Inverse(NImage *pImg)
{
	BYTE	*lpBuf;
 	int		x,y;
    
 	GetImageParament(pImg);              

 	for (y=0;y<nHeight;y++) 
	{
		lpBuf=(BYTE*) pImg->GetPixelAddress(0,y);
		for (x=0;x<nWidth;x++,lpBuf++) 
			*lpBuf = 255 - *lpBuf;
	}

	return true;
}

bool NImgProcess::SingleThresholding(NImage *pImg, int threshold)
{
	BYTE	*lpBuf;
 	int		x,y;
    
 	GetImageParament(pImg);              

 	for (y=0;y<nHeight;y++) 
	{
		lpBuf=(BYTE*) pImg->GetPixelAddress(0,y);
		for (x=0;x<nWidth;x++,lpBuf++) 
		{
			if (*lpBuf >= threshold) *lpBuf=255;
			else		        	 *lpBuf=0;
		}
	}

	return true;
}

bool NImgProcess::OtsuThresholding(NImage *pImg, NImage *pImg2)
{
	BYTE	**list, **list2;
	BYTE	*lpBuf, *lpBuf2;
	long	pg[256];
 	int		x,y,thres;
    
 	GetImageParament(pImg);          

	if (pImg2->GetWidth() != nWidth || pImg2->GetHeight() != nHeight)
		return false;

	list=(BYTE**) Create2DList(pImg);
	list2 = (BYTE**)Create2DList(pImg2);

	histog(list,pg,0,0,nWidth,nHeight);
 
	thres = Otsu(pg);
	
 	for (y=0;y<nHeight;y++) 
	{
		lpBuf=(BYTE*) pImg->GetPixelAddress(0,y);
		lpBuf2 = (BYTE*)pImg2->GetPixelAddress(0, y);
		for (x=0; x<nWidth; x++, lpBuf++, lpBuf2++)
		{
			if (*lpBuf >= thres)*lpBuf2=255;
			else		        *lpBuf2=0;
		}
	}

	Release2DList(list);
	Release2DList(list2);

	return true;
}

bool NImgProcess::Sobel(NImage *pImg)
{
	BYTE	**list1, **list0;
	NImage  Img1;

	GetImageParament(pImg);
	Img1.Create(nWidth, nHeight, nBitCount, 0);

	list0 = (BYTE**)Create2DList(pImg);
	list1 = (BYTE**)Create2DList(&Img1);

	Sobel_core(list0, list1, nWidth, nHeight);

	ArrayCopy(list0, list1, nWidth, nHeight);

	Release2DList(list0);
	Release2DList(list1);


	Img1.Destroy();

	return true;
}

bool NImgProcess::Laplacian(NImage *pImg)
{
	BYTE	**list1, **list0;
	NImage  Img1;

	GetImageParament(pImg);
	Img1.Create(nWidth, nHeight, nBitCount, 0);

	list0 = (BYTE**)Create2DList(pImg);
	list1 = (BYTE**)Create2DList(&Img1);

	Laplacian_core(list0, list1, nWidth, nHeight);

	ArrayCopy(list0, list1, nWidth, nHeight);

	Release2DList(list0);
	Release2DList(list1);


	Img1.Destroy();

	return true;
}

bool NImgProcess::Mean(NImage *pImg)
{
	BYTE	**list1, **list0;
	NImage  Img1;

	GetImageParament(pImg);
	Img1.Create(nWidth, nHeight, nBitCount, 0);

	list0 = (BYTE**)Create2DList(pImg);
	list1 = (BYTE**)Create2DList(&Img1);

	Mean_core(list0, list1, nWidth, nHeight);

	ArrayCopy(list0, list1, nWidth, nHeight);

	Release2DList(list0);
	Release2DList(list1);


	Img1.Destroy();

	return true;
}

bool NImgProcess::Subtract(NImage *pSrcImg, NImage *pRefImg)
{
	BYTE	*lpSrcBuf, *lpRefBuf;	
	int		x, y;
	int		sub_value;

	GetImageParament(pSrcImg);

	if (pRefImg->GetWidth() != nWidth || pRefImg->GetHeight() != nHeight)
		return false;

	for (y = 0; y < nHeight; y++)
	{
		lpSrcBuf = (BYTE*)pSrcImg->GetPixelAddress(0, y);
		lpRefBuf = (BYTE*)pRefImg->GetPixelAddress(0, y);
		for (x = 0; x < nWidth; x++, lpSrcBuf++, lpRefBuf++)
		{
			sub_value = *lpSrcBuf - *lpRefBuf;
			
			if (sub_value < 0) sub_value = 0;

			*lpSrcBuf = sub_value;
		}
			
	}

	return true;
}

bool NImgProcess::BitwiseXOR(NImage *pSrcImg, NImage *pRefImg)
{
	BYTE	*lpSrcBuf, *lpRefBuf;
	int		x, y;

	GetImageParament(pSrcImg);

	if (pRefImg->GetWidth() != nWidth || pRefImg->GetHeight() != nHeight)
		return false;

	for (y = 0; y < nHeight; y++)
	{
		lpSrcBuf = (BYTE*)pSrcImg->GetPixelAddress(0, y);
		lpRefBuf = (BYTE*)pRefImg->GetPixelAddress(0, y);
		for (x = 0; x < nWidth; x++, lpSrcBuf++, lpRefBuf++)
			*lpSrcBuf = (*lpSrcBuf) ^ (*lpRefBuf);

	}

	return true;
}

bool NImgProcess::Inverse_SIMD(NImage *pImg)
{
	BYTE	*lpBuf;
	int		x, y;

	GetImageParament(pImg);


	__m128i	m_invert, m_src;
	__m128i	para = _mm_set1_epi8(255);

	for (y = 0; y < nHeight; y++)
	{
		lpBuf = (BYTE*)pImg->GetPixelAddress(0, y);

		// SIMD Accelerating
		for (x = 0; x <= nWidth - 16; x += 16, lpBuf += 16)
		{
			m_src = _mm_loadu_si128((const __m128i*)(lpBuf));
			m_invert = _mm_subs_epu8(para, m_src);

			_mm_storeu_si128((__m128i*)(lpBuf), m_invert);
		}

		for (; x < nWidth; x++, lpBuf++)
			*lpBuf = 255 - *lpBuf;
	}

	return true;
}

bool NImgProcess::SingleThresholding_SIMD(NImage *pImg, int threshold)
{
	BYTE	*lpBuf;
	int		x, y;

	GetImageParament(pImg);

	__m128i	m_thres, m_src;
	__m128i	para = _mm_set1_epi8(threshold);

	for (y = 0; y < nHeight; y++)
	{
		lpBuf = (BYTE*)pImg->GetPixelAddress(0, y);

		// SIMD Accelerating
		for (x = 0; x <= nWidth - 16; x += 16, lpBuf += 16)
		{
			m_src = _mm_loadu_si128((const __m128i*)(lpBuf));
			m_thres = _mm_cmpeq_epi8(_mm_max_epu8(m_src, para), m_src); //GreaterOrEqual8u(__m128i a, __m128i b)

			_mm_storeu_si128((__m128i*)(lpBuf), m_thres);
		}

		for (; x < nWidth; x++, lpBuf++)
		{
			if (*lpBuf >= threshold) *lpBuf = 255;
			else		        	 *lpBuf = 0;
		}
	}

	return true;
}

bool NImgProcess::Dilation3x3(NImage *pImg, NImage *pImg2)
{
	BYTE	**list1, **list0;

	GetImageParament(pImg);
	
	if (pImg2->GetWidth() != nWidth || pImg2->GetHeight() != nHeight)
		return false;

	list0 = (BYTE**)Create2DList(pImg);
	list1 = (BYTE**)Create2DList(pImg2);

	for (int i = 1; i < nHeight - 1; i++)
	{
		for (int j = 1; j < nWidth - 1; j++)
		{
			if (list0[i - 1][j - 1] > 0 || list0[i - 1][j] > 0 ||
				list0[i - 1][j + 1] > 0 || list0[i][j - 1] > 0 ||
				list0[i][j] > 0 ||
				list0[i][j + 1] > 0 || list0[i + 1][j - 1] > 0 ||
				list0[i + 1][j] > 0 || list0[i + 1][j + 1] > 0)
			{

				list1[i][j] = 255;
			}
			else
			{
				list1[i][j] = 0;
			}
		}

	}

	Release2DList(list0);
	Release2DList(list1);


	return true;
}

bool NImgProcess::Erosion3x3(NImage *pImg, NImage *pImg2)
{
	BYTE	**list1, **list0;

	GetImageParament(pImg);

	if (pImg2->GetWidth() != nWidth || pImg2->GetHeight() != nHeight)
		return false;

	list0 = (BYTE**)Create2DList(pImg);
	list1 = (BYTE**)Create2DList(pImg2);

	for (int i = 1; i < nHeight - 1; i++)
	{
		for (int j = 1; j < nWidth - 1; j++)
		{
			if (list0[i - 1][j - 1] < 255 || list0[i - 1][j] < 255 ||
				list0[i - 1][j + 1] < 255 || list0[i][j - 1] < 255 ||
				list0[i][j] < 255 ||
				list0[i][j + 1] < 255 || list0[i + 1][j - 1] < 255 ||
				list0[i + 1][j] < 255 || list0[i + 1][j + 1] < 255)
			{

				list1[i][j] = 0;
			}
			else
			{
				list1[i][j] = 255;
			}
		}
	}


	Release2DList(list0);
	Release2DList(list1);

	return true;
}

void NImgProcess::GetImageParament(NImage *pImg)
{
	if (pImg->IsNull()) return;

	nWidth = pImg->GetWidth();
	nHeight = pImg->GetHeight();
	nBitCount = pImg->GetBPP();
	nBytesPerLine = (pImg->GetWidth()*pImg->GetBPP()+31)/32*4;
	nBytesPerPixel = pImg->GetBPP()/8;
	if (pImg->GetBPP()<=8) 
		nNumColors = 1 << pImg->GetBPP();
	else 
		nNumColors = 0;
		
	nSize  = nBytesPerLine*nHeight;
}


BYTE** NImgProcess::Create2DList(NImage *pImg)
{
	int			i;
	BYTE		**list;

 	GetImageParament(pImg);
	list=(BYTE**)malloc(nHeight*sizeof(BYTE*));        
	for (i=0;i<nHeight;i++) 
		list[i]=(BYTE*) pImg->GetPixelAddress(0,i); 

	return(list);
}

void NImgProcess::Release2DList(BYTE** list)
{
	free(list);
}

void NImgProcess::ArrayCopy(BYTE **list0, BYTE **list1, int Dx, int Dy)
{
	int  i, j;

	for (i = 1; i < Dy - 1; i++)
		for (j = 1; j < Dx - 1; j++)
			list0[i][j] = list1[i][j];

}

void NImgProcess::histog(BYTE** list,long* pg,int x, int y, int Dx, int Dy)
{                                                               
	int   i,j;

  	for (i=0;i<256;i++)  pg[i]=0;

	for(i=y;i<y+Dy;i++) 
 		for (j=x;j<x+Dx;j++)  
			pg[list[i][j]]++;	
}

void NImgProcess::Sobel_core(BYTE **list0, BYTE **list1, int Dx, int Dy)
{
	int  i, j, A, B, C;

	for (i = 1; i < Dy - 1; i++)
	{
		for (j = 1; j < Dx - 1; j++)
		{
			A = abs((list0[i - 1][j + 1] + 2 * list0[i][j + 1] + list0[i + 1][j + 1]) -
				(list0[i - 1][j - 1] + 2 * list0[i][j - 1] + list0[i + 1][j - 1]));
			B = abs((list0[i + 1][j - 1] + 2 * list0[i + 1][j] + list0[i + 1][j + 1]) -
				(list0[i - 1][j - 1] + 2 * list0[i - 1][j] + list0[i - 1][j + 1]));

			C = (int)sqrt((double)(A * A + B * B));

			C /= 4;

			if (C > 255) C = 255;

			list1[i][j] = (BYTE)C;
		}
	}
}

void NImgProcess::Laplacian_core(BYTE **list0, BYTE **list1, int Dx, int Dy)
{
	int  i, j, C;

	for (i = 1; i < Dy - 1; i++)
	{
		for (j = 1; j < Dx - 1; j++)
		{
			C = -1 * list0[i - 1][j - 1] - 1 * list0[i - 1][j]
				- 1 * list0[i - 1][j + 1] - 1 * list0[i][j - 1]
				+ 8 * list0[i][j]
				- 1 * list0[i][j + 1] - 1 * list0[i + 1][j - 1]
				- 1 * list0[i + 1][j] - 1 * list0[i + 1][j + 1];


			if (C > 255) C = 255;
			else if (C < 0) C = 0;

			list1[i][j] = (BYTE)C;
		}
	}
}

void NImgProcess::Mean_core(BYTE **list0, BYTE **list1, int Dx, int Dy)
{
	int  i, j, C;

	for (i = 1; i < Dy - 1; i++)
	{
		for (j = 1; j < Dx - 1; j++)
		{
			C = list0[i - 1][j - 1] + list0[i - 1][j]
				+ list0[i - 1][j + 1] + list0[i][j - 1]
				+ list0[i][j]
				+ list0[i][j + 1] + list0[i + 1][j - 1]
				+ list0[i + 1][j] + list0[i + 1][j + 1];


			C /= 9;

			list1[i][j] = (BYTE)C;
		}
	}
}

int NImgProcess::Otsu(long *pg)
{
	int  i, j, p;
	double m0, m1, M0, M1, u, v, w[256];

	M0 = M1 = 0;
	for (i = 0; i < 256; i++)
	{
		M0 += pg[i];     
		M1 += pg[i] * i;
	}

	for (j = 0; j < 256; j++)
	{
		m0 = m1 = 0;
		for (i = 0; i <= j; i++)
		{
			m0 += pg[i];
			m1 += pg[i] * i;
		}

		if (m0) u = m1 / m0;
		else   u = 0;

		if (M0 - m0) v = (M1 - m1) / (M0 - m0);
		else      v = 0;

		w[j] = m0 * (M0 - m0)*(u - v)*(u - v);
	}

	p = MaxMin(w, 1);
	return(p);
}

int  NImgProcess::MaxMin(double* tab,int flag)
{
   double  max,min;
   int     i,p,q;

   max=min=tab[128];		
   p=q=128;
   for (i=0;i<256;i++) 
   {
   
      if (tab[i]>max) 
	  {
	     max=tab[i];	
		 p=i;
      }
	  
	  if (tab[i]<min) 
	  {
		 min=tab[i];	
		 q=i;
	  }
   }
   
   if (flag==1) 
   {
      for (i=0;i<256;i++) 
         tab[i]=120*(max-tab[i])/(max-min);
   }
   else 
   {         
      for (i=0;i<256;i++) 
         tab[i]=120*(tab[i]-min)/(max-min);
	 
	  p=q;
   } 

   return(p);
}

int NImgProcess::Ptile(long* pg,double nn)       
{
   int  i;
   double mm,kk;

   for (i=0,mm=0;i<256;i++) mm+=pg[i];
   
   kk=0;
   for (i=0;i<256;i++) 
   {
	  kk+=(double) pg[i]/mm;
      if (kk>=nn)  break;
   }
   return i;
}