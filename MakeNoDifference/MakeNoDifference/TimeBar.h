#pragma once
#include <Windows.h>
#include <atlImage.h>

void TimeBar(HDC memdc, double isTime, HINSTANCE g_hinst, double width, double height, double bottom, double size, int half, HWND hWnd, COLORREF rgb);

void SetTimerGradation(int isTime, int half, HWND hWnd);

void resetTimerRGB();