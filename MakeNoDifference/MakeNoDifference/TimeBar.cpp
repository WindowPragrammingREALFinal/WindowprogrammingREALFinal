#include "TimeBar.h"

static POINT time[4];
static POINT voez[4];

void TimeBar(HDC memdc, double isTime, HINSTANCE g_hinst, double width, double height, double bottom, double size, int half, HWND hWnd, COLORREF rgb)
{

	static HBRUSH hBrush, oldBrush;
	CImage voezNote;
	WCHAR LoadText[1000];

	wsprintf(LoadText, L"voez.png");
	voezNote.Load(LoadText);
//===========================================================================그라데이션 시작지==========
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	TRIVERTEX vert[2], vert2[2];
	GRADIENT_RECT gtr, gtr2;

	vert[0].x = half - 15;
	vert[0].y = height + ((96 - isTime) * (double)(half - 100) / 96);

	// 그라데이션의 시작색상을 명시한다.
	//vert[0].Red = 0xFFFFFF;
	//vert[0].Green = 0xFFFFFF;
	//vert[0].Blue = 0xFFFFFF;
	//vert[0].Alpha = 255 << 8;

	vert[0].Red = GetRValue(rgb) + 64 << 8;
	vert[0].Green = GetGValue(rgb) + 64 << 8;
	vert[0].Blue = GetBValue(rgb) + 64 << 8;
	vert[0].Alpha = 255 << 8;

	// 그라데이션의 끝좌표를 명시한다.
	vert[1].x = half + 15;
	vert[1].y = height + half - 100;

	// 그라데이션의 끝색상를 명시한다.
	vert[1].Red = GetRValue(rgb) << 8;
	vert[1].Green = GetGValue(rgb) << 8;
	vert[1].Blue = GetBValue(rgb) << 8;
	vert[1].Alpha = 0xFFFFFF;

	gtr.UpperLeft = 0;
	gtr.LowerRight = 1;

	// 가로 방향의 시작지점부터 중앙지점까지 그라데이션 효과를 준다.
	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);



	vert2[0].x = ClientRECT.left;
	vert2[0].y = ClientRECT.top + (ClientRECT.right / 2 - 100) + 150;

	// 그라데이션의 끝색상를 명시한다.
	vert2[0].Red = GetRValue(rgb) << 8;
	vert2[0].Green = GetGValue(rgb) << 8;
	vert2[0].Blue = GetBValue(rgb) << 8;
	vert2[0].Alpha = 0x0000;

	vert2[1].x = ClientRECT.right;
	vert2[1].y = ClientRECT.bottom;

	// 그라데이션의 시작색상을 명시한다.
	vert2[1].Red = 0xFFFFFF;
	vert2[1].Green = 0xFFFFFF;
	vert2[1].Blue = 0xFFFFFF;
	vert2[1].Alpha = 0x0000;

	gtr2.UpperLeft = 0;
	gtr2.LowerRight = 1;

	GradientFill(memdc, vert2, 2, &gtr2, 1, GRADIENT_FILL_RECT_V);
//=====================================================================================================================
	//voezNote.Draw(memdc, half - 50, 150, 100, half - 100, 0, 0, 43, 250);
	time[0].x = half - 25;
	time[0].y = height + ((96 - isTime) * (double)(half - 100) / 96);
	time[1].x = half;
	time[1].y = height + ((96 - isTime) * (double)(half - 100) / 96) - 25;
	time[2].x = half + 25;
	time[2].y = height + ((96 - isTime) * (double)(half - 100) / 96);
	time[3].x = half;
	time[3].y = height + ((96 - isTime) * (double)(half - 100) / 96) + 25;

	voez[0].x = half - 20;
	voez[0].y = height + ((96 - isTime) * (double)(half - 100) / 96);
	voez[1].x = half;
	voez[1].y = height + ((96 - isTime) * (double)(half - 100) / 96) - 20;
	voez[2].x = half + 20;
	voez[2].y = height + ((96 - isTime) * (double)(half - 100) / 96);
	voez[3].x = half;
	voez[3].y = height + ((96 - isTime) * (double)(half - 100) / 96) + 20;

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);

//	Rectangle(memdc, half - 25, height + ((96 - isTime) * (double)(half - 100) / 96), half + 25, height + half - 100);

	// Rectangle(memdc, width - 25, height + ((96 - isTime) * (double)(bottom - 100 - height) / 96), width + size + 25, bottom - 100);
	
	hBrush = CreateSolidBrush(RGB(0, 00, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, time, 4);

	hBrush = CreateSolidBrush(RGB(255, 20, 20));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, voez, 4);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}