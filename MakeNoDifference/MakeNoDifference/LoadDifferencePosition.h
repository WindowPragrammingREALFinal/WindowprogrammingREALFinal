#pragma once
#include <Windows.h>
#include <atlImage.h>

void LoadDifferenctPosition(int root, HWND hWnd);

BOOL checkDifference(int x, int y, int correct, int right);

void correctAnimation(HDC memdc, int correct, HINSTANCE g_hinst, int right);