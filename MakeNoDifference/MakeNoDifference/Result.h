#pragma once
#include <Windows.h>
#include <fstream>

void Result(HDC memdc, int score, WCHAR name[], WCHAR studentNumber[], int slide, int score_digit, bool return_but_on,HWND hWnd);

void saveData(int score, WCHAR name[100], WCHAR studentNumber[20]);