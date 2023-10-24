// 下列 ifdef 區塊是建立巨集以協助從 DLL 匯出的標準方式。
// 這個 DLL 中的所有檔案都是使用命令列中所定義 NIMAGEDLL_EXPORTS 符號編譯的。
// 在命令列定義的符號。任何專案都不應定義這個符號
// 這樣一來，原始程式檔中包含這檔案的任何其他專案
// 會將 MYDLL_API 函式視為從 DLL 匯入的，而這個 DLL 則會將這些符號視為
// 匯出的。

#include <windows.h>

#define MYDLL_API __declspec(dllexport)


MYDLL_API LONG_PTR __cdecl CreateNImage();
MYDLL_API bool  __cdecl DestroyNImage(LONG_PTR m_Img);
MYDLL_API bool  __cdecl LoadBMP(LONG_PTR m_Img ,char* filename);
MYDLL_API HBITMAP* __cdecl GetBitmap(LONG_PTR m_Img);
