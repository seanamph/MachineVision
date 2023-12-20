// NObjectDLL.cpp : 定義 DLL 應用程式的匯出函式。
//
#include "NObjectDLL.h"
#include "NImage.h"
#include "NObject.h"


// 這是匯出函式的範例。
NOBJECTDLL_API LONG_PTR __cdecl CreateNObject()
{
	return (LONG_PTR) new NObject();
}


NOBJECTDLL_API bool __cdecl DestroyNObject(LONG_PTR m_Obj)
{
	NObject *Obj = (NObject*)m_Obj;

	if (Obj) delete Obj;

	return true;

}

NOBJECTDLL_API  int	__cdecl Blob_Labelling(LONG_PTR m_Img, LONG_PTR m_Obj)
{
	NImage *Img = (NImage*)m_Img;
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Blob_Labelling(Img));
}

NOBJECTDLL_API  int	__cdecl Contour_Tracing(LONG_PTR m_Img, LONG_PTR m_Obj, int blob_num, int *ct_x, int  *ct_y)
{
	NImage *Img = (NImage*)m_Img;
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Contour_Tracing(Img, blob_num, ct_x, ct_y));
}

NOBJECTDLL_API  int	__cdecl Area(LONG_PTR m_Obj, int blob_num)
{
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Area(blob_num));
}

NOBJECTDLL_API  int	__cdecl Blob_Count(LONG_PTR m_Obj)
{
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Blob_Count());
}

NOBJECTDLL_API  bool __cdecl Rect(LONG_PTR m_Obj, int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h)
{
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->Rectangle(blob_num, start_x, start_y, rect_w, rect_h));
}

NOBJECTDLL_API  bool __cdecl CreateMaskFromObject(LONG_PTR m_Mask_Img, LONG_PTR m_Obj, int blob_num)
{
	NImage *Mask_Img = (NImage*)m_Mask_Img;
	NObject *Obj = (NObject*)m_Obj;

	return (Obj->CreateMaskFromObject(Mask_Img, blob_num));
}
