#pragma once

#ifndef		_INC_PROCESSH
#define		_INC_PROCESSH


void  Threshold(NImage *pImg);
 
int   Otsu(long *pg);                                              
int   KSW_Entropic(long *pg);                        
int   Moment(long *pg);       

void  histog(BYTE **list,long *pg,int x, int y, int Dx, int Dy);  
int   MaxMin(double *tab,int flag);
int   Ptile(long *pg,double nn); 
#endif  //!_INC_PROCESSH


 