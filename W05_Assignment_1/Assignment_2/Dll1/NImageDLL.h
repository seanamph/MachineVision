// �U�C ifdef �϶��O�إߥ����H��U�q DLL �ץX���зǤ覡�C
// �o�� DLL �����Ҧ��ɮ׳��O�ϥΩR�O�C���ҩw�q NIMAGEDLL_EXPORTS �Ÿ��sĶ���C
// �b�R�O�C�w�q���Ÿ��C����M�׳������w�q�o�ӲŸ�
// �o�ˤ@�ӡA��l�{���ɤ��]�t�o�ɮת������L�M��
// �|�N MYDLL_API �禡�����q DLL �פJ���A�ӳo�� DLL �h�|�N�o�ǲŸ�����
// �ץX���C

#include <windows.h>

#ifdef NIMAGEDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

MYDLL_API LONG_PTR __cdecl CreateNImage();
MYDLL_API LONG_PTR __cdecl CreateNImageEx(int wid, int hei);

MYDLL_API bool  __cdecl DestroyNImage(LONG_PTR m_Img);
MYDLL_API bool  __cdecl LoadBMP(LONG_PTR m_Img, char* filename);
MYDLL_API bool  __cdecl SaveBMP(LONG_PTR m_Img, char* filename);
MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR m_Img);

MYDLL_API int __cdecl GetWidth(LONG_PTR m_Img);
MYDLL_API int __cdecl GetHeight(LONG_PTR m_Img);
MYDLL_API int __cdecl GetSize(LONG_PTR m_Img);
MYDLL_API bool __cdecl MemCopy(LONG_PTR m_Img, BYTE *ptr, int wid, int hei);

// Mean filter (3x3)
MYDLL_API void __cdecl MeanFilter3x3(LONG_PTR m_Img);

// Sobel filter
MYDLL_API void __cdecl SobelFilter(LONG_PTR m_Img);

// Laplacian filter
MYDLL_API void __cdecl LaplacianFilter(LONG_PTR m_Img);

MYDLL_API void __cdecl Threshold(LONG_PTR m_Img);

MYDLL_API void __cdecl AdaptiveMeanThreshold(LONG_PTR m_Img, int blockSize);
MYDLL_API void __cdecl AdaptiveGaussianThreshold(LONG_PTR m_Img, int blockSize);
MYDLL_API int __cdecl Blob_Labelling(LONG_PTR m_Img);
MYDLL_API int __cdecl Contour_Tracing(LONG_PTR m_Img);
MYDLL_API int __cdecl CalculateBlobArea(LONG_PTR m_Img);

#ifdef __cplusplus
}
#endif