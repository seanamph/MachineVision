#pragma warning(disable:4996)
#include <stdio.h>
#include <cmath>
#include "NGauge.h"

#define  PI	3.141592653589793238462643383279

using namespace std;

NGauge::NGauge()
{

}

NGauge::~NGauge()
{

}

int  NGauge::SubPixel_EdgeDetector(NImage *pImg, NImage *pMaskImg, double *sub_x, double *sub_y)
{
	BYTE	**list0, **MaskList;

	list0 = (BYTE**)Create2DList(pImg);
	MaskList = (BYTE**)Create2DList(pMaskImg);

	int num = SubPixel_core(list0, MaskList, pImg->GetWidth(), pImg->GetHeight(), sub_x, sub_y);

	
	Release2DList(list0);
	Release2DList(MaskList);


	return num;

}
/************************************************************************/
/*
Circle fit to a given set of data points (in 2D)

I. Kasa, "A curve fitting procedure and its error analysis",
IEEE Trans. Inst. Meas., Vol. 25, pages 8-14, (1976)

The method is based on the minimization of the function

F = sum [(x-a)^2 + (y-b)^2 - R^2]^2

This is perhaps the simplest and fastest circle fit.*/
bool NGauge::CircleFitByKasa(double *edgelist_x, double *edgelist_y, int edge_num, double *result_x,
							 double *result_y, double *result_r)
{
	double Xi, Yi, Zi;
	double Mxy, Mxx, Myy, Mxz, Myz;
	double B, C, G11, G12, G22, D1, D2;
	double edge_mean_x, edge_mean_y;

	Mxx = Myy = Mxy = Mxz = Myz = 0.0;
	edge_mean_x = edge_mean_y = 0;


	for (int i = 0; i < edge_num; i++)
	{
		edge_mean_x += edgelist_x[i];
		edge_mean_y += edgelist_y[i];
	}

	edge_mean_x /= edge_num;
	edge_mean_y /= edge_num;

	for (int i = 0; i < edge_num; i++)
	{

		Xi = edgelist_x[i] - edge_mean_x;   //  centered x-coordinates
		Yi = edgelist_y[i] - edge_mean_y;   //  centered y-coordinates
		Zi = Xi * Xi + Yi * Yi;

		Mxx += Xi * Xi;
		Myy += Yi * Yi;
		Mxy += Xi * Yi;
		Mxz += Xi * Zi;
		Myz += Yi * Zi;
	}

	Mxx /= edge_num;
	Myy /= edge_num;
	Mxy /= edge_num;
	Mxz /= edge_num;
	Myz /= edge_num;

	//solving system of equations by Cholesky factorization
	G11 = sqrt(Mxx);

	if (fabs(G11) < 0.00001)
	{
		*result_x = *result_y = *result_r = 0;
		return false;
	}

	G12 = Mxy / G11;
	G22 = sqrt(Myy - G12 * G12);

	if (fabs(G22) < 0.00001)
	{
		*result_x = *result_y = *result_r = 0;
		return false;
	}

	D1 = Mxz / G11;
	D2 = (Myz - D1 * G12) / G22;

	//computing parameters of the fitting circle
	C = D2 / G22 / 2.0;
	B = (D1 - G12 * C) / G11 / 2.0;

	//assembling the output
	*result_x = B + edge_mean_x;
	*result_y = C + edge_mean_y;
	*result_r = sqrt(B*B + C * C + Mxx + Myy);

	return true;
}


int NGauge::SubPixel_core(BYTE **list0, BYTE **MaskList, int wid, int hei, double *sub_x, double *sub_y)
{
	int  	i, j, Dx, Dy, Di;
	double 	MagG, direction;

	double	*magMat1D = (double*)malloc(wid*hei*sizeof(double));
	double	**magMat = (double**)malloc(hei*sizeof(double*));

	int		*diMat1D = (int*)malloc(wid*hei*sizeof(int));
	int		**diMat = (int**)malloc(hei*sizeof(int*));

	for (i = 0; i < hei; i++)
	{
		magMat[i] = magMat1D + i * wid;
		diMat[i] = diMat1D + i * wid;
	}


	for (i = 1; i < hei - 1; i++)
	{
		for (j = 1; j < wid - 1; j++)
		{
			if (MaskList[i][j] < 255) continue;
			
			// Dx				Dy
			// -1 	0 	1		1 	2 	1	
			// -2 	0 	2   	0 	0 	0
			// -1 	0 	1   	-1 	-2 	-1

			Dx = (list0[i - 1][j + 1] + 2 * list0[i][j + 1] + list0[i + 1][j + 1]) -
				(list0[i - 1][j - 1] + 2 * list0[i][j - 1] + list0[i + 1][j - 1]);
			Dy = (list0[i - 1][j - 1] + 2 * list0[i - 1][j] + list0[i - 1][j + 1]) -
				(list0[i + 1][j - 1] + 2 * list0[i + 1][j] + list0[i + 1][j + 1]);


			MagG = sqrt((Dx*Dx) + (Dy*Dy));  	 //Magnitude = Sqrt(dx^2 +dy^2)
			direction = 180 * atan2(Dy, Dx) / PI;	 //Direction = atan2 (dy / dx)

			if ((direction >= -22.5 && direction < 22.5))
				Di = 0;
			else if ((direction >= 22.5 && direction < 67.5))
				Di = 1;
			else if (direction >= 67.5 && direction < 112.5)
				Di = 2;
			else if ((direction >= 112.5 && direction < 157.5))
				Di = 3;
			else if ((direction >= 157.5 && direction < -157.5))
				Di = 4;
			else if ((direction >= -157.5 && direction < -112.5))
				Di = 5;
			else if ((direction >= -112.5 && direction < -67.5))
				Di = 6;
			else if ((direction >= -67.5 && direction < -22.5))
				Di = 7;

			magMat[i][j] = MagG;
			diMat[i][j] = Di;
		}
	}

	int 	m_num = 0;
	double	s = 0;
	double	leftPixel, rightPixel;
	for (i = 1; i < hei - 1; i++)
	{
		for (j = 1; j < wid - 1; j++)
		{
			MagG = magMat[i][j];
			Di = diMat[i][j];

			if (MagG <= 0) continue;

			switch (Di)
			{
			case 0:
				leftPixel = magMat[i][j - 1];
				rightPixel = magMat[i][j + 1];
				break;
			case 1:
				leftPixel = magMat[i + 1][j - 1];
				rightPixel = magMat[i - 1][j + 1];
				break;
			case 2:
				leftPixel = magMat[i + 1][j];
				rightPixel = magMat[i - 1][j];
				break;
			case 3:
				leftPixel = magMat[i + 1][j + 1];
				rightPixel = magMat[i - 1][j - 1];
				break;
			case 4:
				leftPixel = magMat[i][j + 1];
				rightPixel = magMat[i][j - 1];
				break;
			case 5:
				leftPixel = magMat[i - 1][j + 1];
				rightPixel = magMat[i + 1][j - 1];
				break;
			case 6:
				leftPixel = magMat[i - 1][j];
				rightPixel = magMat[i + 1][j];
				break;
			case 7:
				leftPixel = magMat[i - 1][j - 1];
				rightPixel = magMat[i + 1][j + 1];
				break;
			}

			// compare current pixels value with adjacent pixels and estimate subpixel
			if ((MagG > leftPixel) && (MagG > rightPixel))
				s = (rightPixel - leftPixel) / (4 * MagG - 2 * (rightPixel - leftPixel));		// s = (G+ - G-)/(4*G0-2*(G+ + G-))
			else if (MagG == leftPixel) 	s = -0.5;
			else if (MagG == rightPixel) 	s = 0.5;
			else						  	s = -1;

			if (s > 0 && s <= 0.5)
			{
				sub_x[m_num] = j + s * cos(Di * 45 * PI / 180.0);
				sub_y[m_num] = i - s * sin(Di * 45 * PI / 180.0);

				m_num++;
			}
			else if (s < 0 && s >= -0.5)
			{
				sub_x[m_num] = j - s * cos(Di * 45 * PI / 180.0);
				sub_y[m_num] = i + s * sin(Di * 45 * PI / 180.0);

				m_num++;
			}
		}
	}
	
	free(magMat1D);
	free(magMat);

	free(diMat1D);
	free(diMat);

	return m_num;
}

BYTE** NGauge::Create2DList(NImage *pImg)
{
	int			i;
	BYTE		**list;

	list = (BYTE**)malloc(pImg->GetWidth() * sizeof(BYTE*));
	for (i = 0; i < pImg->GetHeight(); i++)
		list[i] = (BYTE*)pImg->GetPixelAddress(0, i);

	return(list);
}

void NGauge::Release2DList(BYTE** list)
{
	free(list);
}