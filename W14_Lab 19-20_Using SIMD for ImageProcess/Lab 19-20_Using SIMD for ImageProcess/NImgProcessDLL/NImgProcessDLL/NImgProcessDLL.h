// 下列 ifdef 區塊是建立巨集以協助從 DLL 匯出的標準方式。
// 這個 DLL 中的所有檔案都是使用命令列中所定義 MYDLL_EXPORTS 符號編譯的。
// 在命令列定義的符號。任何專案都不應定義這個符號
// 這樣一來，原始程式檔中包含這檔案的任何其他專案
// 會將 MYDLL_API 函式視為從 DLL 匯入的，而這個 DLL 則會將這些符號視為
// 匯出的。

#include <windows.h>

#ifdef NIMGPROCESSDLL_EXPORTS
#define NIMGPROCESSDLL_API __declspec(dllexport)
#else
#define NIMGPROCESSDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

NIMGPROCESSDLL_API  LONG_PTR __cdecl CreateNImgProcess();
NIMGPROCESSDLL_API  bool	__cdecl DestroyNImgProcess(LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	Inverse(LONG_PTR m_Img, LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	SingleThresholding(LONG_PTR m_Img, LONG_PTR m_ImgPro, int threshold);
NIMGPROCESSDLL_API	bool	__cdecl	OtsuThresholding(LONG_PTR m_Img, LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	Sobel(LONG_PTR m_Img, LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	Laplacian(LONG_PTR m_Img, LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	Mean(LONG_PTR m_Img, LONG_PTR m_ImgPro);

NIMGPROCESSDLL_API	bool	__cdecl	Subtract(LONG_PTR m_SrcImg, LONG_PTR m_RefImg, LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	BitwiseXOR(LONG_PTR m_SrcImg, LONG_PTR m_RefImg, LONG_PTR m_ImgPro);

// SIMD
NIMGPROCESSDLL_API	bool	__cdecl	Inverse_SIMD(LONG_PTR m_Img, LONG_PTR m_ImgPro);
NIMGPROCESSDLL_API	bool	__cdecl	SingleThresholding_SIMD(LONG_PTR m_Img, LONG_PTR m_ImgPro, int threshold);

#ifdef __cplusplus
}
#endif