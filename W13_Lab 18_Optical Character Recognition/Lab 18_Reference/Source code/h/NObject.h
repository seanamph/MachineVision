// NObject.h: interface for the NObject class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <stdio.h>
#include <windows.h>

#include "NImage.h"

#ifndef		_NOBJECT_H
#define		_NOBJECT_H

#define		MAX_DOTN  100000
#define		MAX_NUM   60000

struct TAB 																				// �u�q���c
{
	int  label, x1, x2, y, flag;
};

class NObject
{
private:
	//member variables
	int			nWidth;
	int			nHeight;
	int			nBitCount;
	int			nBytesPerLine;
	int			nBytesPerPixel;
	int			nNumColors;
	int			nSize;

	int			blob_count;
	int			tab_count;
	int			blob_area[1000][2];
	int			*m_chain;
	struct TAB	*m_tab;

private:
	//member functions
	void  	GetImageParament(NImage* pImg);

	BYTE** 	Create2DList(NImage* pImg);
	void  	Release2DList(BYTE** list);

	int		LineCoding(BYTE **list, struct TAB *tab,int area[][2], int &tab_size, int wid, int hei);	// �s����u�q�s�X
	void	SearchArea(struct TAB *tab, int num, int flag);  							// �H4/8�s�q�覡�j���s�q�ϰ�(�u�q�s�X�B�J2, 3, 4)
	int		CreateLineTableIndex(struct TAB *tab, int num, int area[][2], int a_n);		// �إ߳s�q�ϰ��Ư��ު�

	int		CreateTab(BYTE **list, int x, int y, int wid, int hei, struct TAB *tab);  	// �إ߽u�q���ê�l��(�u�q�s�X�B�J1)
	int		MakeLabel(struct TAB *tab, int num, int data[][2], int flag);				// ��u�q�@�аO(�u�q�s�X�B�J2)
	void	UniformLabel(struct TAB *tab, int num, int data[][2], int d_num);			// �Τ@�u�q�s�X(�u�q�s�X�B�J3)
	void	SortLabel(struct TAB *tab, int num);										// �u�q���аO�Ƨ�(�u�q�s�X�B�J4)

	void	CentreGravity(struct TAB *tab, int dot_n, double *px, double *py);			// �p��ϰ쭫��

	int		SingleTrack(BYTE **list, int i, int j, int iop, int *code, int flag,
						int wid, int hei);												// �����l��
	int		Perimeter(int *code); 														// �p��P��
	void	OutRectangle(int *code, int *x1, int *y1, int *x2, int *y2);				// �p��~���x��

public:
	NObject();
	~NObject();

public:
	//member functions
	int		Blob_Labelling(NImage* pImg);												// �s������Ҥ�(�u�q�s�X)
	int		Contour_Tracing(NImage* pImg, int blob_num, int *ct_x, int  *ct_y);			// �����l��
	int		Area(int blob_num);															// �p�⭱�n
	int		Blob_Count();																// �^�ǭӼ�

	bool	Rectangle(int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h);// �p��~���x��
	bool	CreateMaskFromObject(NImage* pMask_Img, int blob_num);						// �Q�� Blob ���G�ȤƾB�n
};

#endif		//!_NOBJECT_H