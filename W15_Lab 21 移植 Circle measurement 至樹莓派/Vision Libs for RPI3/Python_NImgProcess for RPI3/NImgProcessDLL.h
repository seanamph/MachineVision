#ifdef NIMAGEDLL_EXPORTS
#define NIMGPROCESSDLL_API __attribute__ ((visibility ("default")))
#else
#define NIMGPROCESSDLL_API __attribute__ ((visibility ("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

NIMGPROCESSDLL_API  unsigned long 	CreateNImgProcess();
NIMGPROCESSDLL_API  bool			DestroyNImgProcess(unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			Inverse(unsigned long m_ImgPro, u_char *m_Img, int wid, int hei);
NIMGPROCESSDLL_API	bool			SingleThresholding(unsigned long m_ImgPro, u_char *m_Img, int wid, int hei, int threshold);
NIMGPROCESSDLL_API	bool			OtsuThresholding(unsigned long m_ImgPro, u_char *m_Img, int wid, int hei);

#ifdef __cplusplus
}
#endif