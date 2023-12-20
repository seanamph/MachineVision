// NObject.cpp: implementation of the NObject class.
// Linux Version
//////////////////////////////////////////////////////////////////////
#include "NObject.h"

NObject::NObject()
{
	nWidth = 0;
	nHeight = 0;
	nBitCount = 0;
	nBytesPerLine = 0;
	nBytesPerPixel = 0;
	nNumColors = 0;
	nSize = 0;

	blob_count = 0;
	tab_count = 0;

	m_chain = (int*) malloc(sizeof(int)*MAX_DOTN);
	m_tab = (struct TAB *) malloc(sizeof(struct TAB)*MAX_DOTN);
}

NObject::~NObject()
{
	if (m_tab!= NULL)  free (m_tab);
	if (m_chain != NULL)  free(m_chain);
}

int	NObject::Blob_Labelling(NImage* pImg)
{
	u_char	**list;

	GetImageParament(pImg);

	list = (u_char**)Create2DList(pImg);

	if (m_tab != NULL)	memset(m_tab, 0, sizeof(struct TAB)*MAX_DOTN);
	else				return 0;

	memset(&blob_area[0][0], 0, sizeof(int) * 2000);

	blob_count = LineCoding(list, m_tab, blob_area, tab_count, nWidth, nHeight);

	Release2DList(list);

	return blob_count;
}

int	NObject::Contour_Tracing(NImage* pImg, int blob_num, int *ct_x, int *ct_y)
{
	u_char	**list;
	int		k = 0;
	int		chain_count = 0;
	int		inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
						{-1, 0},{-1,+1},{ 0,+1},{+1,+1} };					// 鏈碼中鄰點與中心點的坐標差值表

	GetImageParament(pImg);

	list = (u_char**)Create2DList(pImg);

	if (m_tab == NULL || blob_count <= 0)	return 0;
	
	if (m_chain == NULL) memset(m_chain, 0, sizeof(int)*MAX_DOTN);

	int start_x = m_tab[blob_area[blob_num][0]].x1;
	int start_y = m_tab[blob_area[blob_num][0]].y;

	chain_count = SingleTrack(list, start_x, start_y, 4, m_chain, 8, nWidth, nHeight);

	int x = m_chain[0];														// 鏈碼表的前三個元素分別代表 起始座標X、座標Y與鏈碼數量
	int y = m_chain[1];
	for (int i = 0; i < m_chain[2]; i++)
	{
		k = m_chain[i+3];
		x += inc[k][0];
		y += inc[k][1];
		
		ct_x[i] = x;
		ct_y[i] = y;
	}

	Release2DList(list);

	return chain_count;
}

int NObject::Blob_Count()
{
	return (blob_count);
}

int NObject::Area(int blob_num)
{
	if (blob_num < blob_count) return (blob_area[blob_num][1]);
	else                       return 0;

}

bool	NObject::Rectangle(int blob_num, int *start_x, int *start_y, int *rect_w, int *rect_h)
{
	if (m_tab == NULL || blob_count <= 0)	return false;

	int rect_r = 0, rect_d = 0;
	int rect_l = m_tab[blob_area[blob_num][0]].x2;
	int rect_t = m_tab[blob_area[blob_num][0]].y;
	for (int i = blob_area[blob_num][0]; i < blob_area[blob_num + 1][0]; i++)
	{
		if (m_tab[i].y < rect_t) rect_t = m_tab[i].y;
		if (m_tab[i].y > rect_d) rect_d = m_tab[i].y;

		if (m_tab[i].x1 < rect_l) rect_l = m_tab[i].x1;
		if (m_tab[i].x2 > rect_r) rect_r = m_tab[i].x2;
	}

	*start_x = rect_l;
	*start_y = rect_t;
	*rect_w = rect_r - rect_l + 1;
	*rect_h = rect_d - rect_t + 1;

	return true;
}

bool NObject::CreateMaskFromObject(NImage* pMask_Img, int blob_num)
{
	if (pMask_Img->GetWidth() != nWidth || pMask_Img->GetHeight() != nHeight)
		return false;

	u_char	**list;
	int		i, j, k;

	list = (u_char**)Create2DList(pMask_Img);

	for (i = 0; i < nHeight; i++)
		for (j = 0; j < nWidth; j++)
			list[i][j] = 0;

	if (m_tab == NULL || blob_count <= 0)	return false;

	// 將選擇的 Blob 填色(255)
	for (i= blob_area[blob_num][0]; i < blob_area[blob_num + 1][0]; i++)
	{
		k = m_tab[i].y;
		for (j = m_tab[i].x1; j <= m_tab[i].x2; j++)
			list[k][j] = 255;
	}
		
	Release2DList(list);

	return true;
}

void NObject::GetImageParament(NImage *pImg)
{
	if (pImg->IsNull()) return;

	nWidth = pImg->GetWidth();
	nHeight = pImg->GetHeight();
	nBitCount = pImg->GetBPP();
	nBytesPerLine = (pImg->GetWidth()*pImg->GetBPP() + 31) / 32 * 4;
	nBytesPerPixel = pImg->GetBPP() / 8;
	if (pImg->GetBPP() <= 8)
		nNumColors = 1 << pImg->GetBPP();
	else
		nNumColors = 0;

	nSize = nBytesPerLine * nHeight;
}

u_char** NObject::Create2DList(NImage *pImg)
{
	int			i;
	u_char		**list;

	GetImageParament(pImg);
	list = (u_char**)malloc(nHeight * sizeof(u_char*));
	for (i = 0; i < nHeight; i++)
		list[i] = (u_char*)pImg->GetPixelAddress(0, i);

	return(list);
}

void NObject::Release2DList(u_char** list)
{
	free(list);
}

int NObject::LineCoding(u_char **list, struct TAB *tab, int area[][2], int &tab_size, int wid, int hei)
{
	int		num, an;

	if (tab == NULL)  
		return 0;
	
	num = CreateTab(list, 0, 0, wid, hei, tab);
	SearchArea(tab, num, 8);

	an = CreateLineTableIndex(tab, num, area, 1000);

	tab_size = num;

	area[an][0] = num;

	return an;
}

void NObject::SearchArea(struct TAB *tab, int num, int flag)
{
	int  data[1000][2], d_num;

	d_num = MakeLabel(tab, num, data, flag);
	UniformLabel(tab, num, data, d_num);
	SortLabel(tab, num);
}

int NObject::CreateLineTableIndex(struct TAB *tab, int num, int area[][2], int a_n)
{
	int		i, j, k, m, t;

	for (i = 0; i < a_n; i++) area[i][0] = num;
	j = tab[0].label;
	k = m = t = 0;

	for (i = 0; i <= num; i++)
	{
		if (tab[i].label != j)
		{
			area[k][0] = m;
			area[k][1] = t;
			j = tab[i].label;
			k++;
			m = i;
			t = 0;
		}

		t += tab[i].x2 - tab[i].x1 + 1;
		if (k == a_n - 1) break;
	}

	return(k);
}

int NObject::CreateTab(u_char **list, int x, int y, int Dx, int Dy, struct TAB *tab)
{
	int   i, j, k, f, num;

	for (i = y, num = 0; i < y + Dy; i++)
	{
		for (j = x, k = 0, f = 0; j < x + Dx; j++)
		{
			if (list[i][j]) k++;
			else if (k) f = 1;

			if ((j == x + Dx - 1) && (k > 0))
			{
				j++;
				f = 1;
			}

			if (f == 1)
			{
				tab[num].label = 0;
				tab[num].x1 = j - k;
				tab[num].y = i;
				tab[num].x2 = j - 1;
				num++;
				f = k = 0;
			}
		}
	}

	return(num);
}

int NObject::MakeLabel(struct TAB *tab, int num, int data[][2], int flag)
{
	int  line[1000];
	int  i, j, k0, k1, k2, t, no, d_num;
	int  m, n, x1l, x1r, x2l, x2r, y, end, color;

	if (flag == 8) no = 1;
	else  no = 0;

	tab[num].y = 0;
	y = -1;
	for (i = 0, end = 0; i <= num; i++)
	{
		if (tab[i].y != y)
		{
			line[end++] = i;
			y = tab[i].y;
		}
	}

	color = 1;
	k0 = k1 = line[0];
	d_num = 0;

	for (t = 0; t < end; t++)
	{
		k2 = line[t];
		for (i = k0; i < k1; i++)
		{
			y = tab[i].y;		m = tab[i].label;
			x1l = tab[i].x1;	x1r = tab[i].x2;
			for (j = k1; j < k2; j++)
			{
				if (tab[j].y != y + 1) break;
				n = tab[j].label;
				x2l = tab[j].x1;	x2r = tab[j].x2;

				if ((x1l <= x2r + no) && (x2l <= x1r + no))
				{
					if (m == n) continue;
					if (n == 0)
					{
						n = tab[j].label = m;
					}
					else
					{
						if (n < m)
						{
							data[d_num][0] = n;
							data[d_num][1] = m;
						}
						else
						{
							data[d_num][0] = m;
							data[d_num][1] = n;
						}

						d_num++;
					}
				}
			}
		}

		for (j = k1; j < k2; j++)
		{
			if (tab[j].label == 0)
				tab[j].label = color++;
		}

		k0 = k1;
		k1 = k2;
	}

	return(d_num);
}

void NObject::UniformLabel(struct TAB *tab, int num, int data[][2], int d_num)
{
	int  i, j, k, m, n;

	for (i = 0; i < d_num - 1; i++)
	{
		k = i;
		n = data[i][0];

		for (j = i + 1; j < d_num; j++)
		{
			if (data[j][0] < n)
			{
				k = j;
				n = data[j][0];
			}
		}

		m = data[i][0];            n = data[i][1];
		data[i][0] = data[k][0];   data[i][1] = data[k][1];
		data[k][0] = m;            data[k][1] = n;
	}

	for (i = d_num - 1; i >= 0; i--)
	{
		m = data[i][0];
		n = data[i][1];

		for (j = 0; j < num; j++)
		{
			if (tab[j].label == n)
				tab[j].label = m;
		}

		for (j = 0; j < i; j++)
		{
			if (data[j][0] == n)  data[j][0] = m;
			if (data[j][1] == n)  data[j][1] = m;
		}
	}
}

void NObject::SortLabel(struct TAB * tab, int num)
{
	int  i, j, k, n;
	struct TAB temp;

	for (i = 0; i < num - 1; i++)
	{
		k = i;
		n = tab[i].label;

		for (j = i + 1; j < num; j++)
		{
			if (tab[j].label < n)
			{
				k = j;
				n = tab[j].label;
			}
		}

		if (i != k)
		{
			memcpy(&temp, &tab[i], sizeof(struct TAB));
			memcpy(&tab[i], &tab[k], sizeof(struct TAB));
			memcpy(&tab[k], &temp, sizeof(struct TAB));
		}
	}
}

void NObject::CentreGravity(struct TAB *tab, int tab_n, double *px, double *py)
{
	int    i;
	double len, xyu, yyu, sss;

	xyu = yyu = sss = 0;

	for (i = 0; i < tab_n; i++)
	{
		len = (tab[i].x2 - tab[i].x1 + 1);
		sss += len;
		xyu += len * (tab[i].x2 + tab[i].x1) / 2;
		yyu += len * tab[i].y;
	}

	xyu = xyu / sss;
	yyu = yyu / sss;

	*px = xyu;
	*py = yyu;
}

int NObject::SingleTrack(u_char **list, int i, int j, int iop, int *code, int flag, int wid, int hei)
{
	int  kw, code_n;
	int  curr[2], next[2];
	int  n, n1, u, ki, kj, ns, ne;

	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
					 {-1, 0},{-1,+1},{ 0,+1},{+1,+1} };					// 鏈碼中鄰點與中心點的坐標差值表

	if (flag == 4) u = 2;
	else         u = 1;

	code[0] = curr[0] = next[0] = i;
	code[1] = curr[1] = next[1] = j;
	code_n = 3;
	code[3] = -1;

	do
	{
		kw = 0;
		ns = iop;    ne = ns - 8;

		for (n = ns; n > ne; n -= u)
		{
			n1 = (n + 8) % 8;
			ki = curr[0] + inc[n1][0];
			kj = curr[1] + inc[n1][1];

			if (ki < wid && ki >= 0 && kj < hei && kj >= 0)
			{
				if (list[kj][ki] > 0) 										// 可在此設定閥值
					break;
			}
		}

		if (n != ne)
		{
			next[0] = ki;
			next[1] = kj;
			iop = n1;
		}
		else  kw = 1;

		if ((curr[0] == i) && (curr[1] == j) && (iop == code[3]))  break;

		code[code_n++] = iop;
		curr[0] = next[0];
		curr[1] = next[1];

		if ((flag == 8) && (iop % 2 == 0)) iop--;

		iop = (iop + 2) % 8;

		if (code_n >= MAX_DOTN-1) break;

	} while (kw == 0);

	code[2] = code_n - 3;

	return(code_n - 3);
}

int NObject::Perimeter(int *code)
{
	int i, e = 0, ppp = 0, n;

	n = code[2];

	for (i = 3; i < n + 3; i++)
	{
		if (code[i] % 2) e++;
		else  ppp++;
	}

	ppp = (int)(ppp + (1.414*e + 0.5));

	return(ppp);
}

void NObject::OutRectangle(int *code, int *x1, int *y1, int *x2, int *y2)
{
	int  i, n, k, x, y, xi, yi, xa, ya;
	int  inc[8][2] = { {+1, 0},{+1,-1},{ 0,-1},{-1,-1},
					 {-1, 0},{-1,+1},{ 0,+1},{+1,+1} };					// 鏈碼中鄰點與中心點的坐標差值表

	n = code[2];
	xi = xa = x = code[0];
	yi = ya = y = code[1];

	for (i = 0; i < n; i++)
	{
		k = code[3 + i];
		x += inc[k][0];
		y += inc[k][1];

		if (x < xi) xi = x;
		if (x > xa) xa = x;
		if (y < yi) yi = y;
		if (y > ya) ya = y;
	}

	*x1 = xi;		*y1 = yi;
	*x2 = xa;		*y2 = ya;
}
