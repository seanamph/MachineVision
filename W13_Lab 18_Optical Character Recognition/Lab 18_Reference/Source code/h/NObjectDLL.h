#pragma once

#include <windows.h>

#ifdef NOBJECTDLL_EXPORTS
#define NOBJECTDLL_API __declspec(dllexport)
#else
#define NOBJECTDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	NOBJECTDLL_API  LONG_PTR	__cdecl CreateNObject();
	NOBJECTDLL_API  bool		__cdecl DestroyNObject(LONG_PTR m_Obj);

	NOBJECTDLL_API  int			__cdecl Blob_Labelling(LONG_PTR m_Img, LONG_PTR m_Obj);
	NOBJECTDLL_API  int			__cdecl Contour_Tracing(LONG_PTR m_Img, LONG_PTR m_Obj, int blob_num, int *ct_x, int  *ct_y);
	NOBJECTDLL_API  int			__cdecl Area(LONG_PTR m_Obj, int blob_num);
	NOBJECTDLL_API  int			__cdecl Blob_Count(LONG_PTR m_Obj);

	NOBJECTDLL_API  bool		__cdecl Rect(LONG_PTR m_Obj, int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h);
	NOBJECTDLL_API  bool		__cdecl CreateMaskFromObject(LONG_PTR m_Mask_Img, LONG_PTR m_Obj, int blob_num);

#ifdef __cplusplus
}
#endif