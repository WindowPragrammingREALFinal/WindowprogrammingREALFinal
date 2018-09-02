#include "ImageLoad.h"
#include <time.h>

CImage MainImage;
CImage DifferenceImage;

void LoadCImagePicture(int pNumber, int differenceNumber)
{
	WCHAR LoadText[1000];
	WCHAR LoadText2[1000];
	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_00.png", pNumber, pNumber);
	MainImage.Load(LoadText);
	wsprintf(LoadText2, L"IMG_03_00\\Stage%d\\IMG_0%d_0%d.png", pNumber, pNumber,differenceNumber);
	DifferenceImage.Load(LoadText2);
}

void DestoryCimage()
{
	MainImage.Destroy();
	DifferenceImage.Destroy();
}

void LoadPicture(HDC memdc, HINSTANCE g_hinst, int left, int top, int right, int bottom, int pNumber, BOOL load)
{

	//WCHAR LoadText[1000];
	//WCHAR LoadText2[1000];
	//wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_00.png", pNumber, pNumber);
	//MainImage.Load(LoadText);
	//wsprintf(LoadText2, L"IMG_03_00\\Stage%d\\IMG_0%d_01.png", pNumber, pNumber);
	//DifferenceImage.Load(LoadText2);
	MainImage.Draw(memdc, left + 17, top + 82, right / 2 - 50, right / 2 - 50, 0, 0, 1024, 1024);
	DifferenceImage.Draw(memdc, right / 2 + 33, top + 82, right / 2 - 50, right / 2 - 50, 0, 0, 1024, 1024);
	
	//MainImage.Destroy();
	//DifferenceImage.Destroy();
}