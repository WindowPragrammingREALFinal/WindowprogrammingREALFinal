#include "LoadDifferencePosition.h"
#include <fstream>
#include <iostream>


typedef struct _correctPos {
	POINT StartPosition = { 0 , 0 };//�ӽ� ��ǥ ����
	POINT EndPosition = { 100, 100 };
	POINT saveCorrectPosition; // Ʋ���� ������ ��ǥ ���̺�
	int size[5];
	int animationCount = 1;
	BOOL animation = FALSE;
}correctPos;

static correctPos Load[5];

void LoadDifferenctPosition(int pNumber, HWND hWnd) // �׸��� �ε�ÿ� �޸��忡�� Ʋ���κ� ��ǥ�� �ε�
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
			Load[i].StartPosition.x = x * (ClientRECT.right / 2 - 100) / 600;
			Load[i].StartPosition.y = y * (ClientRECT.right / 2 - 100) / 600;
			Load[i].EndPosition.x = dx * (ClientRECT.right / 2 - 100) / 600;
			Load[i].EndPosition.y = dy * (ClientRECT.right / 2 - 100) / 600;
			//wsprintf(LoadText, L"%s %d %d %d %d", LoadText,x,y,dx,dy);
		}
		dir.close();
		//MessageBox(hWnd, LoadText, NULL, NULL);
	}
	//for (int i = 0; i < 5; ++i) { // �̰��� ���Ͽ��� ��ǥ���� �ҷ��� �����ϴ°�
	//	Load[i].StartPosition.x = i * 100;
	//	Load[i].StartPosition.y = i * 100;
	//	Load[i].EndPosition.x = (i + 1) * 100;
	//	Load[i].EndPosition.y = (i + 1) * 100;
	//	Load[i].size[i] = 25;
	//	Load[i].animation = FALSE;
	//	Load[i].animationCount = 1;
	//}
	// �̺κп��� position[i].x, position[i].y �� ��ǥ�� �ҷ��� �ּ���!


}

void correctAnimation(HDC memdc, int correct, HINSTANCE g_hinst, int right) // Ʋ���κ��� ������ ������ �ִϸ��̼�
{
	CImage CorrectFoot[5];
	WCHAR LoadText[1000];

	
	for (int i = 0; i < correct; ++i) {
		if (Load[i].saveCorrectPosition.x < right / 2 && Load[i].animation == TRUE) {
			wsprintf(LoadText, L"C_BUTTON\\C_Button.png");
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, (right / 2) + 50 + (Load[i].saveCorrectPosition.x - 50) - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
		}
		else if(Load[i].saveCorrectPosition.x > right / 2 && Load[i].animation == TRUE) {
			wsprintf(LoadText, L"C_BUTTON\\C_Button.png");
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 50 - (right / 2 - 50) - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
		}
		else if (Load[i].saveCorrectPosition.x < right / 2 && Load[i].animation == FALSE) {
			wsprintf(LoadText, L"Collect_E\\C_Button2_%d.png", Load[i].animationCount);
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, (right / 2) + 50 + (Load[i].saveCorrectPosition.x - 50) - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
			Load[i].animationCount++;
			if (Load[i].animationCount == 9)
				Load[i].animation = TRUE;
		}
		else if (Load[i].saveCorrectPosition.x > right / 2 && Load[i].animation == FALSE) {
			wsprintf(LoadText, L"Collect_E\\C_Button2_%d.png", Load[i].animationCount);
			CorrectFoot[i].Load(LoadText);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Draw(memdc, Load[i].saveCorrectPosition.x - 50 - (right / 2 - 50) - 23, Load[i].saveCorrectPosition.y - 23, 46, 46, 0, 0, 256, 256);
			CorrectFoot[i].Destroy();
			Load[i].animationCount++;
			if (Load[i].animationCount == 9)
				Load[i].animation = TRUE;
		}
	}
}

void xAnimation(HDC memdc, int x, int y, int aniCount)
{
	CImage X;
	WCHAR LoadText[1000];

	wsprintf(LoadText, L"C_NO\\C_NO_%d.png", aniCount);
	X.Load(LoadText);
	X.Draw(memdc, x - 23, y - 23, 46, 46, 0, 0, 128, 128);
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

BOOL checkDifference(int x, int y, int correct, int right) // Ŭ�� ��ǥ�� Ʋ����ġ������ Ȯ��
{
	BOOL check = FALSE;
	for (int i = 0; i < 5 - correct; ++i) {
		if (x >= Load[i].StartPosition.x + 50 && x <= Load[i].EndPosition.x + 50 && y >= Load[i].StartPosition.y + 150 && y <= Load[i].EndPosition.y + 150) {
			Load[correct].saveCorrectPosition.x = x;
			Load[correct].saveCorrectPosition.y = y;
			for (int j = i; j < 5 - correct; ++j) {
				Load[j].StartPosition.x = Load[j + 1].StartPosition.x;
				Load[j].StartPosition.y = Load[j + 1].StartPosition.y;
				Load[j].EndPosition.x = Load[j + 1].EndPosition.x;
				Load[j].EndPosition.y = Load[j + 1].EndPosition.y;
			}
			check = TRUE;
			break;
		}
		else if (x >= Load[i].StartPosition.x + right / 2 + 50 && x <= Load[i].EndPosition.x + right / 2 + 50 && y >= Load[i].StartPosition.y + 150 && y <= Load[i].EndPosition.y + 150) {
			Load[correct].saveCorrectPosition.x = x;
			Load[correct].saveCorrectPosition.y = y;
			for (int j = i; j < 5 - correct; ++j) {
				Load[j].StartPosition.x = Load[j + 1].StartPosition.x;
				Load[j].StartPosition.y = Load[j + 1].StartPosition.y;
				Load[j].EndPosition.x = Load[j + 1].EndPosition.x;
				Load[j].EndPosition.y = Load[j + 1].EndPosition.y;
				check = TRUE;
				break;
			}
		}
	}
	if (check == TRUE)
		return true;
	else
		return false;
}


