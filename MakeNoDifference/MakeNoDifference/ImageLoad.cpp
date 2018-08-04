#include "ImageLoad.h"
#include <time.h>


void LoadPicture(HDC memdc, HINSTANCE g_hinst, int reft, int top, int right, int bottom, int pNumber)
{
	CImage MainImage;
	CImage DifferenceImage;
	WCHAR LoadText[1000];
	
	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_00.png", pNumber, pNumber);
	MainImage.Load(LoadText);
	MainImage.Draw(memdc, reft + 50, top + 100, right / 2 - 100, bottom - 170, 0, 0, 2048, 2048);
	
	
	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_01.png", pNumber, pNumber);
	DifferenceImage.Load(LoadText);
	DifferenceImage.Draw(memdc, right / 2 + 50, top + 100, right / 2 - 100, bottom - 170, 0, 0, 2048, 2048);
}