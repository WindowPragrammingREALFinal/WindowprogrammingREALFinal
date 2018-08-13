#pragma once
#include <Windows.h>
#include <atlImage.h>

void Health(HDC memdc, int Life);

void Result(HDC memdc, int score);

BOOL screenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight);

BOOL openScreenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight);