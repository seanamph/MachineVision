//   IProcess.cpp
    
#ifndef		_INC_IPROCESSC
#define		_INC_IPROCESSC

void GetImageParament(NImage *pImg,struct IMAGEPARAMENT *ppImgParam)
{
	if (pImg->IsNull()) return;

	ppImgParam->nWidth   = pImg->GetWidth();
	ppImgParam->nHeight   = pImg->GetHeight();
	ppImgParam->nBitCount  = pImg->GetBPP();
	ppImgParam->nBytesPerLine   = (pImg->GetWidth()*pImg->GetBPP()+31)/32*4;
	ppImgParam->nBytesPerPixel   = pImg->GetBPP()/8;
	
	if (pImg->GetBPP()<=8) 
		ppImgParam->nNumColors= 1 << pImg->GetBPP();
	else 
		ppImgParam->nNumColors= 0;
		
	ppImgParam->nSize  = ppImgParam->nBytesPerLine*ppImgParam->nHeight;
}


BYTE** Create2DList(NImage *pImg)
{
 	struct		IMAGEPARAMENT P;
	int			i;
	BYTE		**list;

 	GetImageParament(pImg,&P);
	list=(BYTE**)malloc(P.nHeight*sizeof(BYTE*));        
	for (i=0;i<P.nHeight;i++) 
		list[i]=(BYTE*) pImg->GetPixelAddress(0,i); 

	return(list);
}

void Release2DList(BYTE** list)
{
	free(list);
}



#endif  //!_INC_IPROCESSC

