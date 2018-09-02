#pragma once
#include <Windows.h>
#include <atlImage.h>

void LoadDifferenctPosition(int root, int difference, HWND hWnd);

BOOL checkDifference(int x, int y, int correct, int right);

void correctAnimation(HDC memdc, int correct, HINSTANCE g_hinst, int right);

void xAnimation(HDC memdc, int x, int y, int aniCount);