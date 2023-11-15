

#include <windows.h>

struct TAB 																	// �u�q���c
{                                
  int  label,x1,x2,y,flag;                                           
};


#define  MAX_DOTN  100000
#define	 MAX_NUM   60000

// Lab_12 Blob_Labelling from line 12 to line 20
int   LineCoding(BYTE **list,int wid,int hei);		  						// �u�q�s�X

void  SearchArea(struct TAB *tab,int num,int flag);  						// �H4/8�۾F�覡�j���۳s���ϰ�(�u�q�s�X�B�J2, 3, 4)
int   CreateLineTableIndex(struct TAB *tab,int num,int area[][2],int a_n);	// �إ߳s�q�ϰ��Ư��ު�

int   CreateTab(BYTE **list,int x, int y, int wid,int hei,struct TAB *tab);	// �إ߽u�q��ê�l��(�u�q�s�X�B�J1)
int   MakeLabel(struct TAB *tab,int num,int data[][2],int flag);			// ��u�q�@�аO(�u�q�s�X�B�J2)
void  UniformLabel(struct TAB *tab,int num,int data[][2],int d_num);		// �Τ@�u�q�s�X(�u�q�s�X�B�J3)
void  SortLabel(struct TAB *tab,int num);									// �u�q���аO�Ƨ�(�u�q�s�X�B�J4)

// Lab_12 Contour Tracing from line 23 to line 24
int   SingleTrack(BYTE **list,int i,int j,int iop,int *code,int flag,
				  int wid,int hei);											// �����l��
				  
// Practice from line 27 to line 29
void  CentreGravity(struct TAB* tab, int dot_n, double* px, double* py);		// �p��ϰ쭫��
int   Perimeter(int *code); 												// �p��P��
void  OutRectangle(int *code,int *x1,int *y1,int *x2,int *y2);				// �p��~���x��
