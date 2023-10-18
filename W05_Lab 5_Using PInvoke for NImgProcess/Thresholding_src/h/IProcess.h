//   IProcess.h

#pragma once

#ifndef		_INC_IPROCESSH
#define		_INC_IPROCESSH

struct IMAGEPARAMENT 
{       
	int		nWidth;
	int		nHeight;
	int		nBitCount;
    int		nBytesPerLine;
	int		nBytesPerPixel;
	int		nNumColors;
	int		nSize;
};

void  GetImageParament(NImage *pImg,struct IMAGEPARAMENT *ppImgParam);

BYTE** Create2DList(NImage *pImgm);
void  Release2DList(BYTE** list);

 
#endif  //!_INC_IPROCESSH
