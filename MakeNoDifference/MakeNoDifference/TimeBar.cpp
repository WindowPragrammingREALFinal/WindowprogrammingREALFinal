#include "TimeBar.h"

static POINT time[4];
static POINT voez[4];
static POINT triangle[3];

struct TimeBarGradation{
	double r = 60;
	double g = 67;
	double b = 120;
};

static TimeBarGradation Gra;
TRIVERTEX vert[2], vert2[2];
GRADIENT_RECT gtr, gtr2;

static COLORREF tempRGB;


void SetTimerGradation(int isTime, int half, HWND hWnd)
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);

	if (isTime > 80) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r -= 1.625;
		Gra.g += 1.125;
		Gra.b += 1.5;
		// 가로 방향의 시작지점부터 중앙지점까지 그라데이션 효과를 준다.
	//	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime > 72 && isTime <= 80) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 6.375;
		Gra.g += 6.625;
		Gra.b += 6.375;
		// 가로 방향의 시작지점부터 중앙지점까지 그라데이션 효과를 준다.
//		GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime > 64 && isTime <= 72) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB)<< 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 9.75;
		Gra.g += 0.625;
		Gra.b -= 3.75;

//		GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
		// 가로 방향의 시작지점부터 중앙지점까지 그라데이션 효과를 준다
	}
	else if (isTime > 56 && isTime <= 64) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 2.75;
		Gra.g += 1;
		Gra.b -= 0.25;

//		GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime > 48 && isTime <= 56) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 4.5;
		Gra.g += 1.125;
		Gra.b -= 4.375;

//		GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime > 40 && isTime <= 48) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 1.75;
		Gra.g += 2;
		Gra.b -= 13.875;

//		GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime < 32 && isTime <= 40) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 0.125;
		Gra.g += 2.625;
		Gra.b += 4.25;

//		GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime < 24 && isTime <= 32) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r += 0.5;
		Gra.g += 5.5;
		Gra.b += 14.75;

	//	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime < 16 && isTime <= 24) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r -= 2.375;
		Gra.g -= 12.5;
		Gra.b -= 6.625;

	//	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
	}
	else if (isTime < 8 && isTime <= 16) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r -= 3.875;
		Gra.g -= 7;
		Gra.b -= 8;
	}
	else if (isTime < 8) {
		vert[0].x = half - 15;
		vert[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);

		vert[0].Red = GetRValue(tempRGB) << 8;
		vert[0].Green = GetGValue(tempRGB) << 8;
		vert[0].Blue = GetBValue(tempRGB) << 8;
		vert[0].Alpha = 255 << 8;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = half + 15;
		//vert[1].y = height + half - 100;
		vert[1].y = (ClientRECT.right / 2 - 50) + 82;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = GetRValue(tempRGB) << 8;
		vert[1].Green = GetGValue(tempRGB) << 8;
		vert[1].Blue = GetBValue(tempRGB) << 8;
		vert[1].Alpha = 0xFFFFFF;

		gtr.UpperLeft = 0;
		gtr.LowerRight = 1;

		Gra.r -= 3.625;
		Gra.g -= 2;
		Gra.b += 2;
	}

	tempRGB = RGB(Gra.r, Gra.g, Gra.b);
}
void TimeBar(HDC memdc, double isTime, HINSTANCE g_hinst, double width, double height, double bottom, double size, int half, HWND hWnd, COLORREF rgb) //타임바
{

	static HBRUSH hBrush, oldBrush;
	HPEN myPen;
	
	HGDIOBJ oldPen;
	CImage timeStone;
	WCHAR timeston[1000];
	wsprintf(timeston, L"time\\Time_button.png");
	timeStone.Load(timeston);
	//===========================================================================그라데이션 시작지==========
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	


	

	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);

	myPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	oldPen = SelectObject(memdc, myPen);
	MoveToEx(memdc, ClientRECT.right / 2 - 2 ,0, NULL);
	LineTo(memdc, ClientRECT.right / 2 - 2, ClientRECT.bottom);
	myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
	oldPen = SelectObject(memdc, myPen);

	timeStone.Draw(memdc, half - 32, 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) - 25, 64, 63, 0, 0, 64, 63);
	timeStone.Destroy();

	
//=====================================================================================================================
	time[0].x = half - 25;
	time[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) - 25;
	time[1].x = half + 25;
	time[1].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) - 25;
	time[2].x = half + 25;
	time[2].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) + 25;
	time[3].x = half - 25;
	time[3].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) + 25;

	voez[0].x = half - 23;
	voez[0].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);
	voez[1].x = half;
	voez[1].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) - 23;
	voez[2].x = half + 23;
	voez[2].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96);
	voez[3].x = half;
	voez[3].y = 135 + (2 * ((double)(half - 120) / 96)) + ((96 - isTime) * (double)(half - 120) / 96) + 23;

	triangle[0].x = half - 26;
	triangle[0].y = 82 + (ClientRECT.right / 2 - 50);
	triangle[1].x = half - 1;
	triangle[1].y = 82 + (ClientRECT.right / 2 - 50) - 25;
	triangle[2].x = half + 24;
	triangle[2].y = 82 + (ClientRECT.right / 2 - 50);

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);
//	Rectangle(memdc, half - 25, height + ((96 - isTime) * (double)(half - 100) / 96), half + 25, height + half - 100);

	// Rectangle(memdc, width - 25, height + ((96 - isTime) * (double)(bottom - 100 - height) / 96), width + size + 25, bottom - 100);
	
	hBrush = CreateSolidBrush(RGB(50, 50, 235));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	//Polygon(memdc, time, 4);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);

	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, triangle, 3);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	//Polygon(memdc, voez, 4);


	DeleteObject(hBrush);
	DeleteObject(oldBrush);
	DeleteObject(myPen);
	DeleteObject(oldPen);
}