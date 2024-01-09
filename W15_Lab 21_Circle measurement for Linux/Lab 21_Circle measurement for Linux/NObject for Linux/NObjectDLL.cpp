// NObjectDLL.cpp : 定義 DLL 應用程式的匯出函式。
// Linux Version

#include "NImage.h"
#include "NObject.h"
#include "NObjectDLL.h"

NOBJECTDLL_API unsigned long CreateNObject()
{
	return (unsigned long) new NObject();
}


NOBJECTDLL_API bool DestroyNObject(unsigned long m_Obj)
{
	NObject *Obj = (NObject*)m_Obj;

	if (Obj) delete Obj;

	return true;

}

NOBJECTDLL_API  int	Blob_Labelling(unsigned long m_Img, unsigned long m_Obj)
{
	NImage *Img = (NImage*)m_Img;
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Blob_Labelling(Img));
}

NOBJECTDLL_API  int	Contour_Tracing(unsigned long m_Img, unsigned long m_Obj, int blob_num, int *ct_x, int  *ct_y)
{
	NImage *Img = (NImage*)m_Img;
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Contour_Tracing(Img, blob_num, ct_x, ct_y));
}

NOBJECTDLL_API  int	Area(unsigned long m_Obj, int blob_num)
{
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Area(blob_num));
}

NOBJECTDLL_API  int	Blob_Count(unsigned long m_Obj)
{
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Blob_Count());
}

NOBJECTDLL_API  bool Rect(unsigned long m_Obj, int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h)
{
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Rectangle(blob_num, start_x, start_y, rect_w, rect_h));
}

NOBJECTDLL_API  bool CreateMaskFromObject(unsigned long m_Mask_Img, unsigned long m_Obj, int blob_num)
{
	NImage *Mask_Img = (NImage*)m_Mask_Img;
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->CreateMaskFromObject(Mask_Img, blob_num));
}
