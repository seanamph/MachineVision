// NImgProcess.h: interface for the NImage Process class.
// Linux Version
//////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef		_NIMGPROCESS_H
#define		_NIMGPROCESS_H


class NImgProcess
{
private:
//member variables
	int		nWidth;
	int		nHeight;

private:
//member functions

	u_char**	Create2DList(u_char *m_Img);
	void  		Release2DList(u_char** list);
	
	void  		histog(u_char** list,long* pg,int x, int y, int Dx, int Dy); 
	int   		Otsu(long* pg);  	
	int   		MaxMin(double* tab,int flag);
	int   		Ptile(long* pg,double nn); 
public:
	NImgProcess();
 	~NImgProcess();
public:
//member functions
	bool	Inverse(u_char *m_Img, int wid, int hei);
	bool	SingleThresholding(u_char *m_Img, int wid, int hei, int threshold);
	bool	OtsuThresholding(u_char *m_Img, int wid, int hei);
};

#endif		//!_NImgProcess_H