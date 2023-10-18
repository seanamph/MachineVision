
#ifndef		_INC_PROCESSC
#define		_INC_PROCESSC


void Threshold(NImage *pImg)
{
 	struct	IMAGEPARAMENT P;
	BYTE	**list,*lpBuf;
	long	pg[256];
 	int		x,y,thre;
    
 	GetImageParament(pImg,&P);              

	list=(BYTE**) Create2DList(pImg);
	histog(list,pg,0,0,P.nWidth,P.nHeight);
 
	thre=Otsu(pg);
	
 	for (y=0;y<P.nHeight;y++) 
	{
		lpBuf=(BYTE*) pImg->GetPixelAddress(0,y);
		for (x=0;x<P.nWidth;x++,lpBuf++) 
		{
			if (*lpBuf >= thre) *lpBuf=255;
			else		        *lpBuf=0;
		}
	}

	Release2DList(list);
}


int Otsu(long *pg)      
{
   int  i,j,p;
   double m0,m1,M0,M1,u,v,w[256];

   M0=M1=0;
   for (i=0;i<256;i++) 
   {
      M0+=pg[i];     M1+=pg[i]*i;
   }
   
   for (j=0;j<256;j++) 
   {
      m0=m1=0;
      for (i=0;i<=j;i++)
	  {
		m0+=pg[i];	 
		m1+=pg[i]*i;
      }
	  
      if (m0) u=m1/m0;
      else   u=0;
	  
      if (M0-m0) v=(M1-m1)/(M0-m0);
      else      v=0;
	  
      w[j]=m0*(M0-m0)*(u-v)*(u-v);
   }

   p=MaxMin(w,1);
   return(p);
}


int KSW_Entropic(long *pg)            
{
   long   i,t,s;
   double p[256],Pt[256],Ht[256],HT,H[256];
   double A,B,C;
  
   for (i=0,s=0;i<256;i++) s+=pg[i];
   for (i=0;i<256;i++) p[i]=((double) pg[i])/s;

   Pt[0]=p[0];
   for (i=1;i<256;i++) Pt[i]=Pt[i-1]+p[i];

   for (i=0;i<256;i++) 
   {
      if (p[i]==0) Ht[i]=0;
	  else  Ht[i]=-p[i]*log(p[i]);
   }
   for (i=1;i<256;i++) Ht[i]+=Ht[i-1];
   
   HT=Ht[255];
   for (i=0;i<256;i++) 
   {
	  A=Pt[i]*(1-Pt[i]);
      if (A>0) A=log(A);
	  
	  B=Pt[i];
	  if (B>0) B=Ht[i]/B;
	  
	  C=1-Pt[i];
	  if (C>0) C=(HT-Ht[i])/C;
	  
	  H[i]=A+B+C;
   }

   t=MaxMin(H,1);
   return(t);
}

int Moment(long *pg)               
{
   long   i,t;
   double m0,m1,m2,m3,p0,C0,C1;

   m0=m1=m2=m3=0;
   for (i=0;i<256;i++) 
   {
      m0+=(double) pg[i];		
	  m1+=(double) pg[i]*i;
      m2+=(double) pg[i]*i*i;
	  m3+=(double) pg[i]*i*i*i;
   }
   
   C0=(m1*m3-m2*m2)/(m0*m2-m1*m1);
   C1=(m1*m2-m0*m3)/(m0*m2-m1*m1);
   p0=0.5-(m1/m0+C1/2)/sqrt(C1*C1-4*C0);
   t=Ptile(pg,p0);
   
   return(t);
}

bool Sobel(BYTE **list0,BYTE **list1,int Dx,int Dy)  //  Sobel 
{
  Sobel0(list0,list1,Dx,Dy,'M');
}

void Sobel0(BYTE **list0,BYTE **list1,int Dx,int Dy,char ch)
{
  int  i,j,A,B,C;
  
  Scale=4;
  
  for (i=1;i<Dy-1;i++) 
  {
    for (j=1;j<Dx-1;j++) 
	{
      A = abs((list1[i-1][j+1]+2*list1[i][j+1]+list1[i+1][j+1])-
	          (list1[i-1][j-1]+2*list1[i][j-1]+list1[i+1][j-1]));
      B = abs((list1[i+1][j-1]+2*list1[i+1][j]+list1[i+1][j+1])-
	          (list1[i-1][j-1]+2*list1[i-1][j]+list1[i-1][j+1]));
			  
      switch(ch) 
	  {
	    case 'M' :
		  C = (int) sqrt((double)(A*A+B*B));
          break;
	    case 'H' :
	      C = A;
	      break;
	    case 'V' :
	      C = B;
	      break;
 	    default :
	      break;
	  }
	  
      C /= Scale;
	  
      if (C>255) C=255;
	  
	  list0[i][j] = C;
	  
	}
  }
}

void histog(BYTE **list,long *pg,int x, int y, int Dx, int Dy)
{                                                               
	int   i,j;

  	for (i=0;i<256;i++)  pg[i]=0;

	for(i=y;i<y+Dy;i++) 
 		for (j=x;j<x+Dx;j++)  
			pg[list[i][j]]++;	
}

int  MaxMin(double *tab,int flag)
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

int Ptile(long *pg,double nn)       
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



#endif  //!_INC_PROCESSC
 