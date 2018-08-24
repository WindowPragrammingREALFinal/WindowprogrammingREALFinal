#include "UI.h"

void Health(HDC memdc, int Life)
{
	CImage health[5];
	WCHAR LoadText[1000];
	WCHAR LoadText2[1000];

	wsprintf(LoadText, L"Health\\helth.png");
	wsprintf(LoadText2, L"Health\\helth2.png");

	for (int i = 0; i < 5; ++i) {
		if (i < Life)
			health[i].Load(LoadText);
		else
			health[i].Load(LoadText2);

		health[i].Draw(memdc, i * 50, 10, 50, 50, 0, 0, 50, 50);
	}
}

void Result(HDC memdc, int score) // 결과창 애니메이션도 있음
{

}

void Start(HDC memdc, int moveX, HWND hWnd)
{
	HBRUSH hBrush, oldBrush;
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	POINT square[4];
	POINT five[5];

	square[0].x = ClientRECT.right / 2 - 50 - moveX;
	square[0].y = ClientRECT.bottom / 2 + 300;
	square[1].x = ClientRECT.right / 2 - moveX;
	square[1].y = ClientRECT.bottom / 2 + 250;
	square[2].x = ClientRECT.right / 2 + 50 - moveX;
	square[2].y = ClientRECT.bottom / 2 + 300;
	square[3].x = ClientRECT.right / 2 - moveX;
	square[3].y = ClientRECT.bottom / 2 + 350;

	five[0].x = ClientRECT.right / 2 - moveX;
	five[0].y = ClientRECT.bottom / 2 + 250;
	five[1].x = ClientRECT.right / 2 + (moveX * 2);
	five[1].y = ClientRECT.bottom / 2 + 250;
	five[2].x = ClientRECT.right / 2 + (moveX * 2) + 50;
	five[2].y = ClientRECT.bottom / 2 + 300;
	five[3].x = ClientRECT.right / 2 + (moveX * 2);
	five[3].y = ClientRECT.bottom / 2 + 350;
	five[4].x = ClientRECT.right / 2 - moveX;
	five[4].y = ClientRECT.bottom / 2 + 350;

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, five, 5);

	hBrush = CreateSolidBrush(RGB(205, 200, 190));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, square, 4);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);

}

BOOL openScreenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight)
{
	BOOL check = FALSE;

	if (right < totalRight / 4) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 50 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), totalRight + 50 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right, top + bottom / 5 * 5 + 2);
	}

	else if (right >= totalRight / 4 && right < (totalRight / 4) * 2) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 50 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)) , top - 2 + ((bottom / 5) * 3), totalRight + 50, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right -(totalRight / 4)), top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right, top + bottom / 5 * 5 + 2);
	}

	else if (right >= (totalRight / 4) * 2 && right < (totalRight / 4) * 3) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 50, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 3), totalRight + 50, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2), top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right, top + bottom / 5 * 5 + 2);
	}

	else if (right >= (totalRight / 4) * 3 && right < (totalRight / 4) * 4) {
		Rectangle(memdc, left, top - 2, totalRight + 50, top + bottom / 5);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 50, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 3), totalRight + 50, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3), top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2), top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) ), top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right, top + bottom / 5 * 5 + 2);
	}

	else if (right >= (totalRight / 4) * 4 && right < (totalRight / 4) * 5) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 50, top + bottom / 5 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 50, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 50, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 3), totalRight + 50, top + bottom / 5 * 4 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4), top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3), top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2), top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top + bottom / 5 * 4 + 2);
	}

	else if (right >= (totalRight / 4) * 5 && right < (totalRight / 4) * 6) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 50, top + bottom / 5 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 50, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 50, top + bottom / 5 * 3 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4), top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3), top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2), top + bottom / 5 * 3 + 2);
	}

	else if (right >= (totalRight / 4) * 6 && right < (totalRight / 4) * 7) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 50, top + bottom / 5 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 50, top + bottom / 5 * 2 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4), top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3), top + bottom / 5 * 2 + 2);
	}

	else if (right >= (totalRight / 4) * 7 && right < (totalRight / 4) * 8) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 50, top + bottom / 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4), top + bottom / 5 + 2);
	}
	else if (right >= (totalRight / 4) * 8)
		check = TRUE;

	return check;
}

BOOL screenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight)
{
	BOOL check = FALSE;
	
	if (right < totalRight / 4) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5 + 2);

		Rectangle(memdc, left + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight, top + bottom / 5 + 2);
	}

	else if (right >= totalRight / 4 && right < (totalRight / 4) * 2) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 50, top + bottom / 5 * 2 + 2);

		Rectangle(memdc, left + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1) , left + (clientRight / 2) + totalRight, top + bottom / 5 * 2 + 2);
	}

	else if (right >= (totalRight / 4) * 2 && right < (totalRight / 4) * 3 ) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 50, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 50, top + bottom / 5 * 3 + 2);

		Rectangle(memdc, left + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1), left + (clientRight / 2) + totalRight, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight, top + bottom / 5 * 3 + 2);
	}

	else if (right >= (totalRight / 4) * 3 && right < (totalRight / 4) * 4) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 50, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 50, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 50, top + bottom / 5 * 4 + 2);

		Rectangle(memdc, left + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1), left + (clientRight / 2) + totalRight, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight, top + bottom / 5 * 4 + 2);
	}
	else if (right >= (totalRight / 4) * 4 && right < (totalRight / 4) * 5) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 50, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 50, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 50, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1), left + (clientRight / 2) + totalRight, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight, top + bottom / 5 * 5 + 2);
	}

	else if (right >= (totalRight / 4) * 5 && right < (totalRight / 4) * 6) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 50, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 50, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight, top + bottom / 5 * 5 + 2);
	}

	else if (right >= (totalRight / 4) * 6 && right < (totalRight / 4) * 7) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2),totalRight + 50 + 2, top + bottom / 5 * 3);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 50, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight, top + bottom / 5 * 5 + 2);
	}

	else if (right >= (totalRight / 4) * 7 && right < (totalRight / 4) * 8) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 50 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), totalRight + 50 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 50, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2  + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight, top + bottom / 5 * 5 + 2);
	}
	else if (right >= (totalRight / 4) * 8) {
		Rectangle(memdc, left, top - 2, totalRight + 50 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 50 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 50 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), totalRight + 50 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), totalRight + 50 + 2, top + bottom / 5 * 5 + 2);

		Rectangle(memdc, left + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight + 2, top + bottom / 5 * 5 + 2);
		check = TRUE;
	}

	return check;
}

void remain(HDC memdc, int correct, HWND hWnd, COLORREF rgb)
{
	RECT ClientRECT;
	static char difference[1000];
	GetClientRect(hWnd, &ClientRECT);
	HBRUSH hBrush, oldBrush;

	POINT left[3];
	POINT center[4];
	POINT right[3];

	center[0].x = ClientRECT.right / 2 - 64;
	center[0].y = ClientRECT.top + 66;
	center[1].x = ClientRECT.right / 2;
	center[1].y = ClientRECT.top + 2;
	center[2].x = ClientRECT.right / 2 + 64;
	center[2].y = ClientRECT.top + 66;
	center[3].x = ClientRECT.right / 2;
	center[3].y = ClientRECT.top + 128;

	left[0].x = ClientRECT.right / 2 - 128;
	left[0].y = ClientRECT.top;
	left[1].x = ClientRECT.right / 2 - 64;
	left[1].y = ClientRECT.top + 64;
	left[2].x = ClientRECT.right / 2 ;
	left[2].y = ClientRECT.top;

	right[0].x = ClientRECT.right / 2;
	right[0].y = ClientRECT.top;
	right[1].x = ClientRECT.right / 2 + 64;
	right[1].y = ClientRECT.top + 64;
	right[2].x = ClientRECT.right / 2 + 128;
	right[2].y = ClientRECT.top;

	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) -30, GetGValue(rgb) - 30, GetBValue(rgb) - 30));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, left, 3);
	
	hBrush = CreateSolidBrush(RGB(170, 170, 170));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, center, 4);
	
	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) - 60, GetGValue(rgb) - 60, GetBValue(rgb) - 60));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, right, 3);

	wsprintf((LPWSTR)difference, TEXT("%d"), 5 - correct);
	SetBkColor(memdc, RGB(170, 170, 170));
	TextOut(memdc, ClientRECT.right / 2 - 7, ClientRECT.top + 55, (LPWSTR)difference ,1);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}


void setting()
{
	// 폐기 예정
}

void bottomBar(HDC memdc, COLORREF rgb, HWND hWnd)
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	TRIVERTEX vert[2];
	GRADIENT_RECT gtr;


	vert[0].x = ClientRECT.left;
	vert[0].y = ClientRECT.top + (ClientRECT.right / 2 - 100) + 135;

	// 그라데이션의 끝색상를 명시한다.
	vert[0].Red = GetRValue(rgb) << 8;
	vert[0].Green = GetGValue(rgb) << 8;
	vert[0].Blue = GetBValue(rgb) << 8;
	vert[0].Alpha = 0x0000;

	vert[1].x = ClientRECT.right;
	vert[1].y = ClientRECT.bottom;

	// 그라데이션의 시작색상을 명시한다.
	vert[1].Red = 0xFFFFFF;
	vert[1].Green = 0xFFFFFF;
	vert[1].Blue = 0xFFFFFF;
	vert[1].Alpha = 0x0000;

	gtr.UpperLeft = 0;
	gtr.LowerRight = 1;

	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);
}