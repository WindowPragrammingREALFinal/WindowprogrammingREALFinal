#include "TimeBar.h"

static POINT time[4];
static POINT voez[4];

void TimeBar(HDC memdc, double isTime, HINSTANCE g_hinst, double width, double height, double bottom, double size, int half)
{

	static HBRUSH hBrush, oldBrush;
	CImage voezNote;
	WCHAR LoadText[1000];

	wsprintf(LoadText, L"voez.png");
	voezNote.Load(LoadText);

	voezNote.Draw(memdc, half - 50, 150, 100, half - 100, 0, 0, 43, 250);
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

	Rectangle(memdc, half - 25, height + ((96 - isTime) * (double)(half - 100) / 96), half + 25, height + half - 100);

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