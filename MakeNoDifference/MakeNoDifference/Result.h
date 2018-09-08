#pragma once
#include <Windows.h>
#include <atlImage.h>
#include <fstream>

void Result(HDC memdc, int score, WCHAR name[], WCHAR studentNumber[], int slide, int score_digit, bool *return_but_on,HWND hWnd, COLORREF rgb);

void saveData(int score, WCHAR name[100], WCHAR studentNumber[20]);

void LoadScoreBG();

void DrawScoreBG(HDC memdc, HWND hWnd);

void ScoreBGDestroy();

void LoadRestartButton();

void DestroyRestartButton();

