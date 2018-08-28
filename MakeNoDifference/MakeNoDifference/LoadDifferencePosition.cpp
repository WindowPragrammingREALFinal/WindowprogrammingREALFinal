#include "LoadDifferencePosition.h"
#include <fstream>
#include <iostream>


typedef struct _correctPos {
	POINT StartPosition;//임시 좌표 설정
	POINT EndPosition;
	POINT saveCorrectPosition; // 틀린거 맞출경우 좌표 세이브
	int size[5];
	int animationCount = 1;
	BOOL animation = FALSE;
	BOOL check = FALSE;
}correctPos;

static correctPos Load[5];

void LoadDifferenctPosition(int pNumber, HWND hWnd) // 그림을 로드시에 메모장에서 틀린부분 좌표를 로드
{
	WCHAR LoadText[1000];
	std::ifstream dir;

	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\IMG_0%d_01.txt", pNumber, pNumber);
	{
		int tmp;
		RECT ClientRECT;
		dir.open(LoadText, std::ios_base::in);
		dir >> tmp;
		GetClientRect(hWnd, &ClientRECT);
		for (int i = 0; i < tmp; i++)
		{
			int x, y, dx, dy;
			dir >> x >> y >> dx >> dy;
			Load[i].StartPosition.x = (x * (ClientRECT.right / 2 - 50) / 600);
			Load[i].StartPosition.y = (y * (ClientRECT.right / 2 - 50) / 600);
			Load[i].EndPosition.x = (dx * (ClientRECT.right / 2 - 50) / 600);
			Load[i].EndPosition.y = (dy * (ClientRECT.right / 2 - 50) / 600);
			Load[i].animationCount = 1;
			Load[i].animation = FALSE;
			Load[i].check = FALSE;
			//wsprintf(LoadText, L"%s %d %d %d %d", LoadText,x,y,dx,dy);
		}
		dir.close();
	}
	// 이부분에서 position[i].x, position[i].y 에 좌표를 불러와 주세요!


}

void correctAnimation(HDC memdc, int correct, HINSTANCE g_hinst, int right) // 틀린부분을 맞춘경우 나오는 애니메이션
{
	CImage CorrectFoot[5];
	WCHAR LoadText[1000];

	
	for (int i = 0; i < correct; ++i) {
		if (Load[i].saveCorrectPosition.x < right / 2 && Load[i].animation == TRUE) {
			wsprintf(LoadText, L"C_BUTTON\\C_Button.png");
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, (right / 2) + 67 + (Load[i].saveCorrectPosition.x - 50) - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
		}
		else if(Load[i].saveCorrectPosition.x > right / 2 && Load[i].animation == TRUE) {
			wsprintf(LoadText, L"C_BUTTON\\C_Button.png");
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 67 - (right / 2 - 50) - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
		}
		else if (Load[i].saveCorrectPosition.x < right / 2 && Load[i].animation == FALSE) {
			wsprintf(LoadText, L"Collect_E\\C_Button2_%d.png", Load[i].animationCount);
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, (right / 2) + 67 + (Load[i].saveCorrectPosition.x - 50) - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
			Load[i].animationCount++;
			if (Load[i].animationCount == 9)
				Load[i].animation = TRUE;
		}
		else if (Load[i].saveCorrectPosition.x > right / 2 && Load[i].animation == FALSE) {
			wsprintf(LoadText, L"Collect_E\\C_Button2_%d.png", Load[i].animationCount);
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 67 - (right / 2 - 50) - 45, Load[i].saveCorrectPosition.y - 45, 90, 90, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
			Load[i].animationCount++;
			if (Load[i].animationCount == 9)
				Load[i].animation = TRUE;
		}
	}
}

void xAnimation(HDC memdc, int x, int y, int aniCount) // 잘못된 위치를 골랐을때 나오는 애니메이션 X
{
	CImage X;
	WCHAR LoadText[1000];

	wsprintf(LoadText, L"C_NO\\C_NO_%d.png", aniCount);
	X.Load(LoadText);
	X.Draw(memdc, x - 45, y - 45, 90, 90, 0, 0, 128, 128);
	X.Destroy();
}

double LengthCheck(double mx, double my, double x, double y)
{
	return sqrt((mx - x)*(mx - x) + (my - y)*(my - y));
}

BOOL InCircle(double mx, double my, double x, double y, double r)
{
	if (LengthCheck(mx, my, x, y) < r)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL checkDifference(int x, int y, int correct, int right) // 클릭 좌표가 틀린위치인지를 확인
{
	BOOL check = FALSE;
	for (int i = 0; i < 5; ++i) {
		if (x >= Load[i].StartPosition.x + 17 && x <= Load[i].EndPosition.x + 17 && y >= Load[i].StartPosition.y + 82 && y <= Load[i].EndPosition.y + 82 && Load[i].check == FALSE) {
			Load[correct].saveCorrectPosition.x = x;
			Load[correct].saveCorrectPosition.y = y;
			Load[i].check = TRUE;
			check = TRUE;
			break;
		}
		else if (x >= Load[i].StartPosition.x + right / 2 + 33 && x <= Load[i].EndPosition.x + right / 2 + 33 && y >= Load[i].StartPosition.y + 82 && y <= Load[i].EndPosition.y + 82 && Load[i].check == FALSE) {
			Load[correct].saveCorrectPosition.x = x;
			Load[correct].saveCorrectPosition.y = y;
			Load[i].check = TRUE;
			check = TRUE;
			break;
		}
	}
	if (check == TRUE)
		return true;
	else
		return false;
}


