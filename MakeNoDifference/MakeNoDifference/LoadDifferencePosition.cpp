#include "LoadDifferencePosition.h"
OPENFILENAME OFN;
static HANDLE hFile;
TCHAR str[100], lpstrFile[100] = L"";
TCHAR filter[100] = L"Every File(*.*)\0*.*\0Text File \0 *.txt;*.doc \0 ";
static POINT position[5];

void LoadDifferenctPosition(int root, HWND hWnd)
{

	memset(&OFN, 0, sizeof(OPENFILENAME)); // √ ±‚»≠
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	for (int i = 0; i < 5; ++i) {
		position[i].x = i * 100;
		position[i].y = i * 100;
	}

	WCHAR LoadText[1000];
	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\save%d.txt", root, root);
	OFN.lpstrInitialDir = LoadText;

	hFile = CreateFile(lpstrFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

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

BOOL checkDifference(int x, int y, int correct)
{
	
	for (int i = 0; i < 5 - correct; ++i) {
		if (InCircle(x, y, position[i].x, position[i].y, 25)) {
			for (int j = i; j < 5 - correct; ++j) {
				position[j].x = position[j + 1].x;
				position[j].y = position[j + 1].y;
			}
			return true;
		}
	}
	return false;
}


