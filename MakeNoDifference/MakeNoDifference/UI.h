#pragma once
#include <Windows.h>
#include <atlImage.h>

void Health(HDC memdc, int Life);

void Result(HDC memdc, int score);

BOOL screenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight);

BOOL openScreenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight);

void remain(HDC memdc, int correct, HWND hWnd, COLORREF rgb);

void Start(HDC memdc, int moveX, HWND hWnd);

void bottomBar(HDC memdc, COLORREF rgb, HWND hWnd);