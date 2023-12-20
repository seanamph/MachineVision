#pragma once

#ifdef NOBJECTDLL_EXPORTS
#define NOBJECTDLL_API __attribute__ ((visibility ("default")))
#else
#define NOBJECTDLL_API __attribute__ ((visibility ("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

	NOBJECTDLL_API  unsigned long	CreateNObject();
	NOBJECTDLL_API  bool			DestroyNObject(unsigned long m_Obj);

	NOBJECTDLL_API  int				Blob_Labelling(unsigned long m_Img, unsigned long m_Obj);
	NOBJECTDLL_API  int				Contour_Tracing(unsigned long m_Img, unsigned long m_Obj, int blob_num, int *ct_x, int  *ct_y);
	NOBJECTDLL_API  int				Area(unsigned long m_Obj, int blob_num);
	NOBJECTDLL_API  int				Blob_Count(unsigned long m_Obj);

	NOBJECTDLL_API  bool			Rect(unsigned long m_Obj, int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h);
	NOBJECTDLL_API  bool			CreateMaskFromObject(unsigned long m_Mask_Img, unsigned long m_Obj, int blob_num);
	
#ifdef __cplusplus
}
#endif