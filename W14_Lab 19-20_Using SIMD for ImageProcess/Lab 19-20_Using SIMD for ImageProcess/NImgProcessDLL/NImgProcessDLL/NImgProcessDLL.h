// �U�C ifdef �϶��O�إߥ����H��U�q DLL �ץX���зǤ覡�C
// �o�� DLL �����Ҧ��ɮ׳��O�ϥΩR�O�C���ҩw�q MYDLL_EXPORTS �Ÿ��sĶ���C
// �b�R�O�C�w�q���Ÿ��C����M�׳������w�q�o�ӲŸ�
// �o�ˤ@�ӡA��l�{���ɤ��]�t�o�ɮת������L�M��
// �|�N MYDLL_API �禡�����q DLL �פJ���A�ӳo�� DLL �h�|�N�o�ǲŸ�����
// �ץX���C

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