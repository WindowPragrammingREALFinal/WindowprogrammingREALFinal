#pragma once
#include <Windows.h>
#include <atlImage.h>

void LoadDifferenctPosition(int root, HWND hWnd);

BOOL checkDifference(int x, int y, int correct);

void correctAnimation(HDC memdc, int correct, HINSTANCE g_hinst);