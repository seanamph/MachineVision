// NImgProcess.cpp: implementation of the NImage Process class.
// Linux_Version
//////////////////////////////////////////////////////////////////////
#include "NImgProcess.h"

NImgProcess::NImgProcess()
{
	nWidth = 0;
	nHeight = 0;
}

NImgProcess::~NImgProcess()
{
	
}

bool NImgProcess::Inverse(u_char *m_Img, int wid, int hei)
{
 	int	i;  

 	for (i = 0; i < wid * hei; i++, m_Img++)
		*m_Img = 255 - *m_Img;

	return true;
}

bool NImgProcess::SingleThresholding(u_char *m_Img, int wid, int hei, int threshold)
{
 	int	i;

 	for (i = 0; i < wid * hei; i++, m_Img++)
	{
		if (*m_Img >= threshold) *m_Img = 255;
		else		        	 *m_Img = 0;
	}

	return true;
}

bool NImgProcess::OtsuThresholding(u_char *m_Img, int wid, int hei)
{
	u_char	**list;
	u_char	*lpBuf;
	long	pg[256];
 	int		thres;
    
	nWidth = wid;
	nHeight = hei;

	list=(u_char**) Create2DList(m_Img);
	histog(list,pg,0,0,nWidth,nHeight);
 
	thres = Otsu(pg);
	
	for (int i = 0; i < nWidth * nHeight; i++, m_Img++)
	{
		if (*m_Img >= thres)	*m_Img = 255;
		else		        	*m_Img = 0;
	}

	Release2DList(list);

	return true;
}


u_char** NImgProcess::Create2DList(u_char *m_Img)
{
	int			i;
	u_char		**list;

	list=(u_char**)malloc(nHeight*sizeof(u_char*));        
	for (i = 0;i < nHeight; i++) 
		list[i]= m_Img + i * nWidth; 

	return(list);
}

void NImgProcess::Release2DList(u_char** list)
{
	free(list);
}

void NImgProcess::histog(u_char** list,long* pg,int x, int y, int Dx, int Dy)
{                                                               
	int   i,j;

  	for (i=0;i<256;i++)  pg[i]=0;

	for(i=y;i<y+Dy;i++) 
 		for (j=x;j<x+Dx;j++)  
			pg[list[i][j]]++;	
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