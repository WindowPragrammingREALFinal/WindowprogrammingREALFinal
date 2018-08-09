#include "TimeBar.h"

void TimeBar(HDC memdc, double isTime, HINSTANCE g_hinst, double width, double height, double bottom, double size)
{
	Rectangle(memdc, width - 25, height + ((96 - isTime) * (double)(bottom - 100 - height) / 96) , width + size + 25, bottom - 100);
}