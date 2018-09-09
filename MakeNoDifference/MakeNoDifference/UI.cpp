#include "UI.h"

void Health(HDC memdc, int Life) //화면의 좌상단 남은 체력 표시
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


	}
	for (int i = 0; i < 5; ++i) {
		health[i].Draw(memdc, i * 50, 10, 50, 50, 0, 0, 50, 50);
		health[i].Destroy();
	}
}


static int tempScore;

void scoreImageLoad(int score)
{

}

void scoreImage(HDC memdc, HWND hWnd, int Totalscore, int count)
{
	WCHAR LoadText[100]; 
	
	RECT ClientRECT;
	HBRUSH hBrush, oldBrush;
	HFONT hFont, oldFont;
	GetClientRect(hWnd, &ClientRECT);



	RECT temp_rect = ClientRECT; // 임시 렉트(점수 출력용)
	temp_rect.left = ClientRECT.right / 2 + 570;
	temp_rect.right = ClientRECT.right - 100;
	temp_rect.top = ClientRECT.top + 20;
	temp_rect.bottom = ClientRECT.top + 80;

	SetTextColor(memdc, RGB(255, 255, 255));
	hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));     // 학번,이름 폰트 조정
	oldFont = (HFONT)SelectObject(memdc, hFont);
	SetBkMode(memdc, TRANSPARENT);
	wsprintf(LoadText, L"%d", Totalscore);
	DrawText(memdc, LoadText, wcslen(LoadText), &temp_rect, DT_CENTER || DT_VCENTER);

	DeleteObject(hFont);
	DeleteObject(oldFont);
}

void Start(HDC memdc, int moveX, HWND hWnd) //임시로 만들어둔 로그인 시작버튼
{
	/*HBRUSH hBrush, oldBrush;
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
	DeleteObject(oldBrush);*/

}

BOOL openScreenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight) //틀린그림 5개를 다맞추고 화면 전환에 쓰임
{
	BOOL check = FALSE;

	if (right < totalRight / 4) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), totalRight + 17 + 2, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= totalRight / 4 && right < (totalRight / 4) * 2) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)) , top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 17 + 2, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right -(totalRight / 4)) + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= (totalRight / 4) * 2 && right < (totalRight / 4) * 3) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 17 + 2, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2) + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right - (totalRight / 4)) + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= (totalRight / 4) * 3 && right < (totalRight / 4) * 4) {
		Rectangle(memdc, left, top - 2, totalRight + 17, top + bottom / 5);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + right, top - 2 + ((bottom / 5) * 4), totalRight + 17 + 2, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3) + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2) + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) ) + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight - right + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= (totalRight / 4) * 4 && right < (totalRight / 4) * 5) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4) + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3) + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2) + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight - (right - (totalRight / 4)) + 20, top + bottom / 5 * 4 + 4);
	}

	else if (right >= (totalRight / 4) * 5 && right < (totalRight / 4) * 6) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4) + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3) + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 2) + 20, top + bottom / 5 * 3 + 4);
	}

	else if (right >= (totalRight / 4) * 6 && right < (totalRight / 4) * 7) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left + (right - ((totalRight / 4) * 3)), top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4) + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 3) + 20, top + bottom / 5 * 2 + 4);
	}

	else if (right >= (totalRight / 4) * 7 && right < (totalRight / 4) * 8) {
		Rectangle(memdc, left + (right - ((totalRight / 4) * 4)), top - 2, totalRight + 17 + 2, top + bottom / 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight - (right - (totalRight / 4) * 4) + 20, top + bottom / 5 + 4);
	}
	else if (right >= (totalRight / 4) * 8)
		check = TRUE;

	return check;
}

BOOL screenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight)//틀린그림 5개를 다맞추고 화면 전환에 쓰임
{
	BOOL check = FALSE;
	
	if (right < totalRight / 4) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5 + 2);

		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight + 20, top + bottom / 5 + 2);
	}

	else if (right >= totalRight / 4 && right < (totalRight / 4) * 2) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 50, top + bottom / 5 * 2 + 2);

		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1) , left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 2 + 2);
	}

	else if (right >= (totalRight / 4) * 2 && right < (totalRight / 4) * 3 ) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 17, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 17, top + bottom / 5 * 3 + 2);

		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 3 + 2);
	}

	else if (right >= (totalRight / 4) * 3 && right < (totalRight / 4) * 4) {
		Rectangle(memdc, left, top - 2, right, top + bottom / 5);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 17, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 17, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 17, top + bottom / 5 * 4 + 2);

		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - right, top - 2, left + (clientRight / 2) + totalRight + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 4 + 2);
	}
	else if (right >= (totalRight / 4) * 4 && right < (totalRight / 4) * 5) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), right - (totalRight / 4) + 17, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 17, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 17, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 17, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - (totalRight / 4)), top - 2 + ((bottom / 5) * 1), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= (totalRight / 4) * 5 && right < (totalRight / 4) * 6) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), right - ((totalRight / 4) * 2) + 17, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 17, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 17, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 2)), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= (totalRight / 4) * 6 && right < (totalRight / 4) * 7) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2),totalRight + 17 + 2, top + bottom / 5 * 3);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), right - ((totalRight / 4) * 3) + 17, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 17, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 3)), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 5 + 4);
	}

	else if (right >= (totalRight / 4) * 7 && right < (totalRight / 4) * 8) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), right - ((totalRight / 4) * 4) + 17, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2  + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2) + totalRight - (right - ((totalRight / 4) * 4)), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight + 20, top + bottom / 5 * 5 + 4);
	}
	else if (right >= (totalRight / 4) * 8) {
		Rectangle(memdc, left, top - 2, totalRight + 17 + 2, top + bottom / 5 + 2);
		Rectangle(memdc, left, top - 2 + (bottom / 5), totalRight + 17 + 2, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 2), totalRight + 17 + 2, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 3), totalRight + 17 + 2, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left, top - 2 + ((bottom / 5) * 4), totalRight + 17 + 2, top + bottom / 5 * 5 + 4);

		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2, left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + (bottom / 5), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 2 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 2), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 3 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 3), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 4 + 2);
		Rectangle(memdc, left + 15 + (clientRight / 2), top - 2 + ((bottom / 5) * 4), left + (clientRight / 2) + totalRight + 2 + 20, top + bottom / 5 * 5 + 4);
		check = TRUE;
	}

	return check;
}




void remain(HDC memdc, int correct, HWND hWnd, COLORREF rgb, int slideY, int slideX) // 화면 중앙부 상단에 위치한 남은 틀린갯수(+ 삼각형, 사각형의 디자인
{
	CImage remainImage;
	RECT ClientRECT;
	WCHAR LoadText[1000];
	static char difference[1000];
	GetClientRect(hWnd, &ClientRECT);
	static HBRUSH hBrush, oldBrush;

	POINT leftTop[3];
	POINT leftBottom[3];
	POINT rightTop[3];
	POINT rightBottom[3];

	leftTop[0].x = ClientRECT.left;
	leftTop[0].y = ClientRECT.top;
	leftTop[1].x = ClientRECT.left + 140 + slideX;
	leftTop[1].y = ClientRECT.top;
	leftTop[2].x = ClientRECT.left;
	leftTop[2].y = ClientRECT.top + 160 + slideY;

	leftBottom[0].x = ClientRECT.left;
	leftBottom[0].y = ClientRECT.bottom;
	leftBottom[1].x = ClientRECT.left + 121 + slideX;
	leftBottom[1].y = ClientRECT.bottom;
	leftBottom[2].x = ClientRECT.left;
	leftBottom[2].y = ClientRECT.top + 900 - slideY;

	rightTop[0].x = ClientRECT.right;
	rightTop[0].y = ClientRECT.top;
	rightTop[1].x = ClientRECT.left + 1782 - slideX;
	rightTop[1].y = ClientRECT.top;
	rightTop[2].x = ClientRECT.right;
	rightTop[2].y = ClientRECT.top + 160 + slideY;

	rightBottom[0].x = ClientRECT.right;
	rightBottom[0].y = ClientRECT.bottom;
	rightBottom[1].x = ClientRECT.right;
	rightBottom[1].y = ClientRECT.top + 900 - slideY;
	rightBottom[2].x = ClientRECT.right - 121 - slideX;
	rightBottom[2].y = ClientRECT.bottom;

	wsprintf(LoadText, L"BG\\UI_Remain.png");
	remainImage.Load(LoadText);
	remainImage.Draw(memdc, 863, 0, 174, 173, 0, 0,174, 173);
	remainImage.Destroy();

	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) + 63, GetGValue(rgb) + 63, GetBValue(rgb) + 63));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, leftTop, 3);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);

	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) + 63, GetGValue(rgb) + 63, GetBValue(rgb) + 63));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, leftBottom, 3);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);

	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) + 63, GetGValue(rgb) + 63, GetBValue(rgb) + 63));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, rightBottom, 3);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);

	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) + 63, GetGValue(rgb) + 63, GetBValue(rgb) + 63));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, rightTop, 3);
	DeleteObject(hBrush);
	DeleteObject(oldBrush);
	//Rectangle(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right / 2 - 64, ClientRECT.top + 66);
	//
	//hBrush = CreateSolidBrush(RGB(170, 170, 170));
	//oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	//Polygon(memdc, center, 4);
	//DeleteObject(hBrush);
	//DeleteObject(oldBrush);
	//
	//hBrush = CreateSolidBrush(RGB(GetRValue(rgb) - 35, GetGValue(rgb) - 45, GetBValue(rgb) - 24));
	//oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	//Polygon(memdc, right, 3);
	//Rectangle(memdc, ClientRECT.right / 2 + 64, ClientRECT.top, ClientRECT.right + 2, ClientRECT.top + 66);


	wsprintf((LPWSTR)difference, TEXT("%d"), 5 - correct);
	SetBkMode(memdc, TRANSPARENT);
	TextOut(memdc, ClientRECT.right / 2 - 10, ClientRECT.top + 55, (LPWSTR)difference ,1);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}

CImage BG;

void BGLoad()
{
	WCHAR LoadText[1000];
	wsprintf(LoadText, L"BG\\배경.png");
	BG.Load(LoadText);
}

void BGDraw(HDC memdc, HWND hWnd)
{
	
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	BG.Draw(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right, ClientRECT.bottom , 0, 0, 1920, 1080);
}

void BGDestroy()
{
	BG.Destroy();
}

CImage UI_Bar;

void bottomBarLoad()
{
	WCHAR LoadText[1000];
	wsprintf(LoadText, L"BG\\상하단.png");
	UI_Bar.Load(LoadText);
}

void bottomBar(HDC memdc, COLORREF rgb, HWND hWnd) //하단부에 위치하며 틀린부분은 찾거나 잘못 골랐을 경우 그라데이션으로 색깔을 나타내며 표시해줌
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	
	UI_Bar.Draw(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right, ClientRECT.bottom, 0, 0, 1920, 1080);
}

void bottomBarDestroy()
{
	UI_Bar.Destroy();
}

void login(HDC memdc, HWND hWnd)
{
	CImage login;
	CImage loginBG;
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	WCHAR LoadText[1000];
	WCHAR LoadText2[1000];
	wsprintf(LoadText2, L"Title\\TITLE_89.png");
	wsprintf(LoadText, L"BG\\UI_login.png");
	loginBG.Load(LoadText);
	login.Load(LoadText2);
	login.AlphaBlend(memdc, ClientRECT, ClientRECT, 0, 255);
	loginBG.Draw(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right, ClientRECT.bottom, 0, 0, 1920, 1080);
	loginBG.Destroy();
}

void signIn(HDC memdc)
{
	CImage signIn;
	WCHAR LoadText[1000];
	wsprintf(LoadText, L"BG\\UI_BT_START.png");
	signIn.Load(LoadText);
	signIn.Draw(memdc, 1543, 396, 256, 256, 0, 0, 256, 256);
	signIn.Destroy();
}