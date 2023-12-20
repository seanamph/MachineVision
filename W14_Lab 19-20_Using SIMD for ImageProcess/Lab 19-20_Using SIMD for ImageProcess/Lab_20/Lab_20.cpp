bool NImgProcess::Subtract(NImage *pSrcImg, NImage *pRefImg)
{
	BYTE	*lpSrcBuf, *lpRefBuf;	
	int		x, y;
	int		sub_value;

	GetImageParament(pSrcImg);

	for (y = 0; y < nHeight; y++)
	{
		lpSrcBuf = (BYTE*)pSrcImg->GetPixelAddress(0, y);
		lpRefBuf = (BYTE*)pRefImg->GetPixelAddress(0, y);
		for (x = 0; x < nWidth; x++, lpSrcBuf++, lpRefBuf++)
		{
			sub_value = *lpSrcBuf - *lpRefBuf;
			
			if (sub_value < 0) sub_value = 0;

			*lpSrcBuf = sub_value;
		}
			
	}

	return true;
}

bool NImgProcess::BitwiseXOR(NImage *pSrcImg, NImage *pRefImg)
{
	BYTE	*lpSrcBuf, *lpRefBuf;
	int		x, y;

	GetImageParament(pSrcImg);

	for (y = 0; y < nHeight; y++)
	{
		lpSrcBuf = (BYTE*)pSrcImg->GetPixelAddress(0, y);
		lpRefBuf = (BYTE*)pRefImg->GetPixelAddress(0, y);
		for (x = 0; x < nWidth; x++, lpSrcBuf++, lpRefBuf++)
			*lpSrcBuf = (*lpSrcBuf) ^ (*lpRefBuf);

	}

	return true;
}