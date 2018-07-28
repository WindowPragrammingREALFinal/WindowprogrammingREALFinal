#include "TimeBar.h"

void TimeBar(HDC memdc, int isTime, HINSTANCE g_hinst, int width, int height, int size)
{
	HDC TimeBarDC = CreateCompatibleDC(memdc);
	Rectangle(memdc, width, (height + (100 - isTime) * 5), width + size, height + 500);


	DeleteDC(TimeBarDC);
}