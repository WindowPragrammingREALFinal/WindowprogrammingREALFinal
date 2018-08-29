#include "ImageLoad.h"
#include <time.h>

static CImage MainImage;
static CImage DifferenceImage;

void LoadCImagePicture(int pNumber)
{
	WCHAR LoadText[1000];
	MainImage.Destroy();
	DifferenceImage.Destroy();
	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_00.png", pNumber, pNumber);
	MainImage.Load(LoadText);
	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_01.png", pNumber, pNumber);
	DifferenceImage.Load(LoadText);
}


void LoadPicture(HDC memdc, HINSTANCE g_hinst, int left, int top, int right, int bottom, int pNumber)
{
	// 게임에 사용되는 틀린그림들 로드후 그리는 위치
	
	//WCHAR LoadText[1000];
	
	//wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_00.png", pNumber, pNumber);
	//MainImage.Load(LoadText);
	MainImage.Draw(memdc, left + 17, top + 82, right / 2 - 50, right / 2 - 50, 0, 0, 1024, 1024);

//	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_01.png", pNumber, pNumber);
//	DifferenceImage.Load(LoadText);
	DifferenceImage.Draw(memdc, right / 2 + 33, top + 82, right / 2 - 50, right / 2 - 50, 0, 0, 1024, 1024);
}