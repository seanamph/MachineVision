// NObject.h: interface for the NObject class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <stdio.h>
#include <windows.h>

#include "NImage.h"

#ifndef		_NOBJECT_H
#define		_NOBJECT_H

#define		MAX_DOTN  10000
#define		MAX_NUM   6000

struct TAB 																				// 線段結構
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

	int		LineCoding(BYTE **list, struct TAB *tab,int area[][2], int &tab_size, int wid, int hei);	// 連結體線段編碼
	void	SearchArea(struct TAB *tab, int num, int flag);  							// 以4/8連通方式搜索連通區域(線段編碼步驟2, 3, 4)
	int		CreateLineTableIndex(struct TAB *tab, int num, int area[][2], int a_n);		// 建立連通區域資料索引表

	int		CreateTab(BYTE **list, int x, int y, int wid, int hei, struct TAB *tab);  	// 建立線段表並初始化(線段編碼步驟1)
	int		MakeLabel(struct TAB *tab, int num, int data[][2], int flag);				// 對線段作標記(線段編碼步驟2)
	void	UniformLabel(struct TAB *tab, int num, int data[][2], int d_num);			// 統一線段編碼(線段編碼步驟3)
	void	SortLabel(struct TAB *tab, int num);										// 線段按標記排序(線段編碼步驟4)

	void	CentreGravity(struct TAB *tab, int dot_n, double *px, double *py);			// 計算區域重心

	int		SingleTrack(BYTE **list, int i, int j, int iop, int *code, int flag,
						int wid, int hei);												// 輪廓追蹤
	int		Perimeter(int *code); 														// 計算周長
	void	OutRectangle(int *code, int *x1, int *y1, int *x2, int *y2);				// 計算外接矩形

public:
	NObject();
	~NObject();

public:
	//member functions
	int		Blob_Labelling(NImage* pImg);												// 連結體標籤化(線段編碼)
	int		Contour_Tracing(NImage* pImg, int blob_num, int *ct_x, int  *ct_y);			// 輪廓追蹤
	int		Area(int blob_num);															// 計算面積

	bool	CreateMaskFromObject(NImage* pMask_Img, int blob_num);						// 利用 Blob 做二值化遮罩
};

#endif		//!_NOBJECT_H