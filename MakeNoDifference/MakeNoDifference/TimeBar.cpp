#include "TimeBar.h"

void TimeBar(HDC memdc, int isTime, HINSTANCE g_hinst, int width, int height, int size)
{
	HDC TimeBarDC = CreateCompatibleDC(memdc);
	Rectangle(memdc, width - 25, (height + (100 - isTime) * 5), width + size + 25, 900 - 150);


	DeleteDC(TimeBarDC);
}