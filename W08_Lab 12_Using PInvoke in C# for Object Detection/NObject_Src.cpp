#include "NObject_Src.h"


int LineCoding(BYTE **list,int wid,int hei) 
{
 	int		area[1000][2];
	int		num,an;
    
 	struct TAB *tab = (struct TAB *) malloc(sizeof(struct TAB)*MAX_DOTN);
	if (tab==NULL)  return;

	num = CreateTab(list,0,0,wid,hei,tab);
	SearchArea(tab,num,8);
 
	an=CreateLineTableIndex(tab,num,area,1000);

	
	free(tab);
	
	return an;
}

void SearchArea(struct TAB *tab,int num,int flag)  
{
	int  data[1000][2],d_num;
 
	d_num = MakeLabel(tab,num,data,flag);        
	UniformLabel(tab,num,data,d_num);          
	SortLabel(tab,num);                        
}

int CreateLineTableIndex(struct TAB *tab,int num,int area[][2],int a_n)
{
	int		i,j,k,m,t;
 
	for (i = 0; i < a_n; i++) area[i][0] = num;
 	j = tab[0].label;
	k = m = t = 0;
	
	for (i=0;i<=num;i++) 
	{           
		if (tab[i].label!=j) 
		{ 
			area[k][0]=m;      
			area[k][1]=t;      
			j=tab[i].label;
 			k++;
			m=i;
			t=0;
		}
		
 		t += tab[i].x2-tab[i].x1+1;
		if (k == a_n-1) break;
	}
	
	return(k);
}

int CreateTab(BYTE **list,int x, int y, int wid,int hei,struct TAB *tab)
{                                    
	int   i,j,k,f,num;
   
	for (i=y,num=0;i<y+hei;i++) 
	{
		for (j=x,k=0,f=0;j<x+wid;j++) 
		{
			if (list[i][j]) k++;                    
			else if (k) f=1;
	  
			if ((j==x+wid-1)&&(k>0)) 
			{
				j++;	
				f=1;
			}
	  
			if (f==1) 
			{
				tab[num].label=0;                
				tab[num].x1=j-k;                
				tab[num].y =i;
				tab[num].x2=j-1;
				num++;                          
				f=k=0;                            
			}
		}
	}
  
  return(num);                          
}

int MakeLabel(struct TAB *tab,int num,int data[][2],int flag)     
{                                
	int  line[1000];
	int  i,j,k0,k1,k2,t,no,d_num;
	int  m,n,x1l,x1r,x2l,x2r,y,end,color;
 
	if (flag==8) no=1;                    
	else  no=0;                           
  
	tab[num].y=0;
	y=-1;
	for (i=0,end=0;i<=num;i++) 
	{          
		if (tab[i].y!=y) 
		{                  
			line[end++]=i;
			y=tab[i].y;
		}
	}
  
	color=1;                  
	k0=k1=line[0];            
	d_num=0;                  
  
	for (t=0;t<end;t++) 
	{
		k2=line[t];                      
		for (i=k0;i<k1;i++) 
		{               
			y=tab[i].y;		m=tab[i].label;      
			x1l=tab[i].x1;	x1r=tab[i].x2;
			for (j=k1;j<k2;j++) 
			{             
				if (tab[j].y!=y+1) break;
				n=tab[j].label;                                       
				x2l=tab[j].x1;	x2r=tab[j].x2;
				
				if ((x1l<=x2r+no)&&(x2l<=x1r+no)) 
				{  
					if (m==n) continue;                          
					if (n==0) 
					{                          
						n=tab[j].label=m;          
					}
					else 
					{           
						if (n<m) 
						{
							data[d_num][0]=n;           
							data[d_num][1]=m;
						}
						else 
						{
							data[d_num][0]=m;           
							data[d_num][1]=n;
						}
					
						d_num++;
					}
				}	
			}
		}
		
		for (j=k1;j<k2;j++) 
		{               
			if (tab[j].label==0) 
				tab[j].label=color++;
		} 
		
		k0=k1;                              
		k1=k2;                              
	}
	
	return(d_num);
}

void UniformLabel(struct TAB *tab,int num,int data[][2],int d_num)
{                                          
	int  i,j,k,m,n;

	for (i=0;i<d_num-1;i++) 
	{             
		k=i;      
		n=data[i][0];
		
		for (j=i+1;j<d_num;j++) 
		{
			if (data[j][0]<n) 
			{
				k=j;		
				n=data[j][0];
			}
		}
    
		m=data[i][0];            n=data[i][1];
		data[i][0]=data[k][0];   data[i][1]=data[k][1];
		data[k][0]=m;            data[k][1]=n;
	}

	for (i=d_num-1;i>=0;i--) 
	{            
		m=data[i][0];	
		n=data[i][1];
		
		for (j=0;j<num;j++) 
		{
			if (tab[j].label==n) 
				tab[j].label=m;
		}
		
		for (j=0;j<i;j++) 
		{
			if (data[j][0]==n)  data[j][0]=m;      
			if (data[j][1]==n)  data[j][1]=m;
		}
	}
}

void SortLabel(struct TAB * tab,int num) 
{
	int  i,j,k,n;
	struct TAB temp;

	for (i=0;i<num-1;i++) 
	{                    
		k=i;      
		n=tab[i].label;
    
		for (j=i+1;j<num;j++) 
		{
			if (tab[j].label<n) 
			{
				k=j;		
				n=tab[j].label;
			}
		}
		
		if (i!=k) 
		{
			memcpy(&temp,&tab[i],sizeof(struct TAB));    
			memcpy(&tab[i],&tab[k],sizeof(struct TAB));
			memcpy(&tab[k],&temp,sizeof(struct TAB));
		}
	}
}

int SingleTrack(BYTE **list,int i,int j,int iop,int *code,int flag,int wid,int hei)
{               
	int  kw,code_n;
	int  curr[2],next[2];               
	int  n,n1,u,ki,kj,ns,ne;
	
	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1,+1},{ 0,+1},{+1,+1}  };					// 鏈碼中鄰點與中心點的坐標差值表
  
	if (flag==4) u=2;
	else         u=1;

	code[0]=curr[0]=next[0]=i;    
	code[1]=curr[1]=next[1]=j;	                     
	code_n=3;	                       
	code[3]=-1;
	
	do 
	{
		kw=0;	                     
		ns=iop;    ne=ns-8;            
      
		for (n=ns;n>ne;n-=u) 
		{    
			n1 = (n+8) % 8;	         
			ki=curr[0]+inc[n1][0];
			kj=curr[1]+inc[n1][1];
			
			if (ki<wid && ki>=0 && kj<hei && kj>=0)
			{	
				if (list[kj][ki] > 0) 										// 可在此設定閥值
					break;	             
			}
		}
		
		if (n!=ne) 
		{                               
			next[0]=ki;  
			next[1]=kj;          
			iop=n1;	                   
		}
		else  kw = 1;	                 
  
		if ((curr[0]==i)&&(curr[1]==j)&&(iop==code[3]))  break;   
		
		code[code_n++]=iop;	                   
		curr[0]=next[0];   
		curr[1]=next[1];      
		
		if ((flag==8)&&(iop%2==0)) iop--; 
		
		iop=(iop+2)%8;	               
	
	} while(kw==0);	                         

	code[2]=code_n-3;	                       
	
	return(code_n-3);
}


void CentreGravity(struct TAB *tab, int tab_n, double *px, double *py)
{
	int    i;
	double len,xyu,yyu,sss;

	xyu=yyu=sss=0;
   
	for (i=0;i<tab_n;i++) 
	{
      len=(tab[i].x2-tab[i].x1+1);  
	  sss+=len;                      
	  xyu += len*(tab[i].x2+tab[i].x1)/2;
	  yyu += len*tab[i].y;               
	}
   
	xyu = xyu/sss;                        
	yyu = yyu/sss;                        
   
	*px=xyu;			
	*py=yyu;
}


int Perimeter(int *code)  
{
	int i,e=0,ppp=0,n;

	n=code[2];
  
	for (i=3;i<n+3;i++) 
	{
		if (code[i]%2) e++;
		else  ppp++;	   
	}
	
	ppp=(int) (ppp+(1.414*e+0.5));
  
	return(ppp);
}

void OutRectangle(int *code,int *x1,int *y1,int *x2,int *y2)
{                                      
	int  i,n,k,x,y,xi,yi,xa,ya;
	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
                     {-1, 0},{-1,+1},{ 0,+1},{+1,+1}  };					// 鏈碼中鄰點與中心點的坐標差值表

	n=code[2];
	xi=xa=x=code[0];			
	yi=ya=y=code[1];
	
	for (i=0;i<n;i++) 
	{
		k=code[3+i];
		x+=inc[k][0];		
		y+=inc[k][1];
		
		if (x<xi) xi=x;
		if (x>xa) xa=x;
		if (y<yi) yi=y;
		if (y>ya) ya=y;
	}
	
	*x1=xi;		*y1=yi;
	*x2=xa;		*y2=ya;
}





