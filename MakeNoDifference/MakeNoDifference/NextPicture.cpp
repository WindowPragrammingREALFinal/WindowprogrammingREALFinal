#include "NextPicture.h"
#include <fstream>
#include <iostream>

static int saveNumber[18];
static int count = 0;
int nextNumber()
{
	int next;
	srand(time(0));
	next = rand() % 18 + 1;
	BOOL check = FALSE;
	BOOL crash = FALSE;

	while (check != TRUE) {
		if (count == 0) {
			check = TRUE;
			saveNumber[count] = next;
			count++;
		}
		else {
			for (int i = 0; i < count; ++i) {
				if (saveNumber[i] == next) {
					next += 1;
					if (next == 19)
						next = 1;
					i = 0;
				}
				if (i == count - 1) {
					saveNumber[count] = next;
					count++;
					check = TRUE;
					break;
				}

			}

		}	
	}
	return next;
}

int differenceNumber(int number)
{
	int load;
	int result;
	WCHAR LoadText[1000];
	std::ifstream dir;

	wsprintf(LoadText, L"IMG_03_00\\Stage%d\\%d.txt", number, number);
	dir.open(LoadText, std::ios_base::in);
	dir >> load;

	result = rand() % load + 1;

	return result;
}

void nowStage(HDC memdc, HWND hWnd)
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	WCHAR is_stage[100];
	wsprintf(is_stage, L"Stage %d", count);
	SetBkMode(memdc, TRANSPARENT);
	TextOut(memdc, ClientRECT.left + 100, ClientRECT.bottom - 50, is_stage, wcslen(is_stage));
}

void countReset()
{
	count = 0;
}

void clearMap()
{
	for (int i = 0; i < 18; ++i)
		saveNumber[i] = 0;
}