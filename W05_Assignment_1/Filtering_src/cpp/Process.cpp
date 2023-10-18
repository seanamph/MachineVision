#include <math.h>


#ifndef		_INC_PROCESSC
#define		_INC_PROCESSC


void Sobel(NImage *pImg)
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list1, **list0;
 	NImage  Img1;

 	GetImageParament(pImg,&P);
	Img1.Create(P.nWidth,P.nHeight,P.nBitCount,0);
	
	list0=(BYTE**) Create2DList(pImg);
	list1=(BYTE**) Create2DList(&Img1);
 
	Sobel_core(list0,list1,P.nWidth,P.nHeight);
	
	ArrayCopy(list0,list1,P.nWidth,P.nHeight);
	
	Release2DList(list0);
	Release2DList(list1);
	
	
	Img1.Destroy();
}

void Sobel_core(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j,A,B,C;
  
  for (i=1;i<Dy-1;i++) 
  {
    for (j=1;j<Dx-1;j++) 
	{
      A = abs((list0[i-1][j+1]+2*list0[i][j+1]+list0[i+1][j+1])-
	          (list0[i-1][j-1]+2*list0[i][j-1]+list0[i+1][j-1]));
      B = abs((list0[i+1][j-1]+2*list0[i+1][j]+list0[i+1][j+1])-
	          (list0[i-1][j-1]+2*list0[i-1][j]+list0[i-1][j+1]));
    
	  C = (int) sqrt((double)(A*A+B*B));

      C /= 4;
	  
      if ( C > 255 ) C=255;
	  
	  list1[i][j] = (BYTE) C;
	}
  }
}

void Laplacian_core(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j,C;
  
  for (i=1;i<Dy-1;i++) 
  {
    for (j=1;j<Dx-1;j++) 
	{
      C = -1*list0[i-1][j-1]-1*list0[i-1][j]
	      -1*list0[i-1][j+1]-1*list0[i][j-1]
	      +8*list0[i][j]
		  -1*list0[i][j+1]-1*list0[i+1][j-1]
	      -1*list0[i+1][j]-1*list0[i+1][j+1];
	      

      if ( C > 255 ) C = 255;
	  else if (C < 0 ) C = 0;
	  
	  list1[i][j] = (BYTE) C;
	}
  }
}

void Mean_core(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j,C;
  
  for (i=1;i<Dy-1;i++) 
  {
    for (j=1;j<Dx-1;j++) 
	{
      C = list0[i-1][j-1]+list0[i-1][j]
	      +list0[i-1][j+1]+list0[i][j-1]
	      +list0[i][j]
		  +list0[i][j+1]+list0[i+1][j-1]
	      +list0[i+1][j]+list0[i+1][j+1];
	      

      C /= 9;

	  list1[i][j] = (BYTE) C;
	}
  }
}

void ArrayCopy(BYTE **list0,BYTE **list1,int Dx,int Dy)
{
  int  i,j;
  
  for (i=1;i<Dy-1;i++) 
    for (j=1;j<Dx-1;j++)
	  list0[i][j] = list1[i][j];
	
}



#endif  //!_INC_PROCESSC
 