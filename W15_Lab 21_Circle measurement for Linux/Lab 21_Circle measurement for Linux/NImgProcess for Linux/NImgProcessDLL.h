
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
NIMGPROCESSDLL_API	bool			Inverse(unsigned long m_Img, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			SingleThresholding(unsigned long m_Img, unsigned long m_ImgPro, int threshold);
NIMGPROCESSDLL_API	bool			OtsuThresholding(unsigned long m_Img, unsigned long m_Img2, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			Sobel(unsigned long m_Img, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			Laplacian(unsigned long m_Img, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			Mean(unsigned long m_Img, unsigned long m_ImgPro);

NIMGPROCESSDLL_API	bool			Subtract(unsigned long m_SrcImg, unsigned long m_RefImg, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			BitwiseXOR(unsigned long m_SrcImg, unsigned long m_RefImg, unsigned long m_ImgPro);

NIMGPROCESSDLL_API	bool			Dilation3x3(unsigned long m_Img, unsigned long m_Img2, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			Erosion3x3(unsigned long m_Img, unsigned long m_Img2, unsigned long m_ImgPro);

NIMGPROCESSDLL_API	bool			Small_Transform(unsigned long m_SrcImg, unsigned long m_OutImg, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			FromImageToVector(unsigned long m_Img, u_char *m_Vector, int element_num, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			Split_Image(unsigned long m_SrcImg, int start_x, int start_y, int split_wid,
												int split_hei, unsigned long m_SubImg, unsigned long m_ImgPro);


// SIMD
NIMGPROCESSDLL_API	bool			Inverse_SIMD(unsigned long m_Img, unsigned long m_ImgPro);
NIMGPROCESSDLL_API	bool			SingleThresholding_SIMD(unsigned long m_Img, unsigned long m_ImgPro, int threshold);

#ifdef __cplusplus
}
#endif