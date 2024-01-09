// �U�C ifdef �϶��O�إߥ����H��U�q DLL �ץX���зǤ覡�C
// �o�� DLL �����Ҧ��ɮ׳��O�ϥΩR�O�C���ҩw�q MYDLL_EXPORTS �Ÿ��sĶ���C
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
MYDLL_API bool  __cdecl LoadBMP(LONG_PTR m_Img ,char* filename);
MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR m_Img);

MYDLL_API int __cdecl GetWidth(LONG_PTR m_Img);
MYDLL_API int __cdecl GetHeight(LONG_PTR m_Img);
MYDLL_API int __cdecl GetSize(LONG_PTR m_Img);
MYDLL_API bool __cdecl MemCopy(LONG_PTR m_Img, BYTE *ptr, int wid, int hei);


#ifdef __cplusplus
}
#endif