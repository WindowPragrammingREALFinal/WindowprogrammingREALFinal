#pragma once
#include <Windows.h>
#include <fstream>

void Result(HDC memdc, int score, int slide, HWND hWnd);

void saveData(int score, WCHAR name[100], WCHAR studentNumber[20]);