

#include <windows.h>

struct TAB 																	// 線段結構
{                                
  int  label,x1,x2,y,flag;                                           
};


#define  MAX_DOTN  100000
#define	 MAX_NUM   60000

// Lab_12 Blob_Labelling from line 12 to line 20
int   LineCoding(BYTE **list,int wid,int hei);		  						// 線段編碼

void  SearchArea(struct TAB *tab,int num,int flag);  						// 以4/8相鄰方式搜索相連接區域(線段編碼步驟2, 3, 4)
int   CreateLineTableIndex(struct TAB *tab,int num,int area[][2],int a_n);	// 建立連通區域資料索引表

int   CreateTab(BYTE **list,int x, int y, int wid,int hei,struct TAB *tab);	// 建立線段表並初始化(線段編碼步驟1)
int   MakeLabel(struct TAB *tab,int num,int data[][2],int flag);			// 對線段作標記(線段編碼步驟2)
void  UniformLabel(struct TAB *tab,int num,int data[][2],int d_num);		// 統一線段編碼(線段編碼步驟3)
void  SortLabel(struct TAB *tab,int num);									// 線段按標記排序(線段編碼步驟4)

// Lab_12 Contour Tracing from line 23 to line 24
int   SingleTrack(BYTE **list,int i,int j,int iop,int *code,int flag,
				  int wid,int hei);											// 輪廓追蹤
				  
// Practice from line 27 to line 29
void  CentreGravity(struct TAB* tab, int dot_n, double* px, double* py);		// 計算區域重心
int   Perimeter(int *code); 												// 計算周長
void  OutRectangle(int *code,int *x1,int *y1,int *x2,int *y2);				// 計算外接矩形
