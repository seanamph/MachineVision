// Linux Version

#ifdef NIMAGEDLL_EXPORTS
#define MYDLL_API __attribute__ ((visibility ("default")))
#else
#define MYDLL_API __attribute__ ((visibility ("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

MYDLL_API unsigned long CreateNImage();
MYDLL_API unsigned long CreateNImageEx(int wid, int hei);
MYDLL_API bool  		DestroyNImage(unsigned long m_Img);
MYDLL_API bool 			LoadBMP(unsigned long m_Img ,char* filename);

MYDLL_API int 			GetWidth(unsigned long m_Img);
MYDLL_API int			GetHeight(unsigned long m_Img);
MYDLL_API int 			GetSize(unsigned long m_Img);
MYDLL_API bool 			MemCopy(unsigned long m_Img, u_char *ptr, int wid, int hei);

MYDLL_API bool 			ReSize(unsigned long m_Img, int wid, int hei);
#ifdef __cplusplus
}
#endif
