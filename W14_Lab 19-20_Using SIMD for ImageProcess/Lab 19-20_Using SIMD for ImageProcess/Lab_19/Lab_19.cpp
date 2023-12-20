//#include <emmintrin.h>		// for SSE2
//#include <tmmintrin.h>		// for SSSE3
#include <immintrin.h>

bool NImgProcess::Inverse_SIMD(NImage *pImg)
{
	BYTE	*lpBuf;
	int		x, y;

	GetImageParament(pImg);


	__m128i	m_invert, m_src;
	__m128i	para = _mm_set1_epi8(255);

	for (y = 0; y < nHeight; y++)
	{
		lpBuf = (BYTE*)pImg->GetPixelAddress(0, y);

		// SIMD Accelerating
		for (x = 0; x <= nWidth - 16; x += 16, lpBuf += 16)
		{
			m_src = _mm_loadu_si128((const __m128i*)(lpBuf));
			m_invert = _mm_subs_epu8(para, m_src);

			_mm_storeu_si128((__m128i*)(lpBuf), m_invert);
		}

		for (; x < nWidth; x++, lpBuf++)
			*lpBuf = 255 - *lpBuf;
	}

	return true;
}

bool NImgProcess::SingleThresholding_SIMD(NImage *pImg, int threshold)
{
	BYTE	*lpBuf;
	int		x, y;

	GetImageParament(pImg);

	__m128i	m_thres, m_src;
	__m128i	para = _mm_set1_epi8(threshold);

	for (y = 0; y < nHeight; y++)
	{
		lpBuf = (BYTE*)pImg->GetPixelAddress(0, y);

		// SIMD Accelerating
		for (x = 0; x <= nWidth - 16; x += 16, lpBuf += 16)
		{
			m_src = _mm_loadu_si128((const __m128i*)(lpBuf));
			m_thres = _mm_cmpeq_epi8(_mm_max_epu8(m_src, para), m_src); //GreaterOrEqual8u(__m128i a, __m128i b)

			_mm_storeu_si128((__m128i*)(lpBuf), m_thres);
		}

		for (; x < nWidth; x++, lpBuf++)
		{
			if (*lpBuf >= threshold) *lpBuf = 255;
			else		        	 *lpBuf = 0;
		}
	}

	return true;
}