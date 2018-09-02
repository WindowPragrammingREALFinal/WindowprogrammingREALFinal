#pragma once
#include <Windows.h>
#include <atlImage.h>

void LoadPicture(HDC memdc, HINSTANCE g_hinst, int left, int top, int right, int bottom, int pNumber, BOOL load);

void LoadCImagePicture(int pNumber, int differenceNumber);

void DestoryCimage();