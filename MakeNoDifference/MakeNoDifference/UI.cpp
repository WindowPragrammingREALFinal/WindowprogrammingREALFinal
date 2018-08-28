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

	//	health[i].Draw(memdc, i * 50, 10, 50, 50, 0, 0, 50, 50);
	}
}

void Result(HDC memdc, int score, int slide, HWND hWnd) // 결과창 애니메이션도 있음
{
	RECT ClientRECT;
	HBRUSH hBrush, oldBrush;
	GetClientRect(hWnd, &ClientRECT);


	hBrush = CreateSolidBrush(RGB(100, 50, 232));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);

	Rectangle(memdc, ClientRECT.left, (ClientRECT.bottom / 5) * 2, slide, (ClientRECT.bottom / 5) * 2 + 3);
	Rectangle(memdc, ClientRECT.right - slide, (ClientRECT.bottom / 5) * 3, ClientRECT.right, (ClientRECT.bottom / 5) * 3 + 3);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}

static int tempScore;
void scoreImage(HDC memdc, HWND hWnd, int Totalscore, int count)
{
	int temp;
	CImage score[6];
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	WCHAR LoadText[1000];

	if (count == 0)
		tempScore = Totalscore;

	wsprintf(LoadText, L"ScoreNumber\\%d\\%d_%d.png", tempScore / 100000, tempScore / 100000, count);
	score[0].Load(LoadText);
	temp = Totalscore % 100000;

	wsprintf(LoadText, L"ScoreNumber\\%d\\%d_%d.png", temp / 10000, temp / 10000, count);
	score[1].Load(LoadText);
	temp %= 10000;

	wsprintf(LoadText, L"ScoreNumber\\%d\\%d_%d.png", temp / 1000, temp / 1000, count);
	score[2].Load(LoadText);
	temp %= 1000;

	wsprintf(LoadText, L"ScoreNumber\\%d\\%d_%d.png", temp / 100, temp / 100, count);
	score[3].Load(LoadText);
	temp %= 100;

	wsprintf(LoadText, L"ScoreNumber\\%d\\%d_%d.png", temp / 10, temp / 10, count);
	score[4].Load(LoadText);
	temp %= 10;

	wsprintf(LoadText, L"ScoreNumber\\%d\\%d_%d.png", temp, temp, count);
	score[5].Load(LoadText);
	
	for (int i = 0; i < 6; ++i)
		score[i].Draw(memdc, ClientRECT.right / 2 + (i * 64) + 550, ClientRECT.top + 25, 64, 64,0,0,64,64);
}

void Start(HDC memdc, int moveX, HWND hWnd) //임시로 만들어둔 로그인 시작버튼
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

void remain(HDC memdc, int correct, HWND hWnd, COLORREF rgb) // 화면 중앙부 상단에 위치한 남은 틀린갯수(+ 삼각형, 사각형의 디자인)
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

	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) -99, GetGValue(rgb) - 66, GetBValue(rgb) - 58));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, left, 3);
	Rectangle(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right / 2 - 64, ClientRECT.top + 66);
	
	hBrush = CreateSolidBrush(RGB(170, 170, 170));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, center, 4);
	
	hBrush = CreateSolidBrush(RGB(GetRValue(rgb) - 35, GetGValue(rgb) - 45, GetBValue(rgb) - 24));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, right, 3);
	Rectangle(memdc, ClientRECT.right / 2 + 64, ClientRECT.top, ClientRECT.right + 2, ClientRECT.top + 66);

	wsprintf((LPWSTR)difference, TEXT("%d"), 5 - correct);
	SetBkColor(memdc, RGB(170, 170, 170));
	TextOut(memdc, ClientRECT.right / 2 - 7, ClientRECT.top + 55, (LPWSTR)difference ,1);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}


void BG(HDC memdc, HWND hWnd)
{
	CImage BG;
	RECT ClientRECT;
	WCHAR LoadText[1000];
	GetClientRect(hWnd, &ClientRECT);

	wsprintf(LoadText, L"BG\\%BG_01.png");
	BG.Load(LoadText);
	BG.Draw(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right, ClientRECT.bottom, 0, 0, 1920, 1080);
	BG.Destroy();
}

void bottomBar(HDC memdc, COLORREF rgb, HWND hWnd) //하단부에 위치하며 틀린부분은 찾거나 잘못 골랐을 경우 그라데이션으로 색깔을 나타내며 표시해줌
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	TRIVERTEX vert[2];
	GRADIENT_RECT gtr;
	HBRUSH hBrush, oldBrush;
	HDC uiDC = CreateCompatibleDC(memdc);

	BLENDFUNCTION t;

	
	

	vert[0].x = ClientRECT.left;
	vert[0].y = ClientRECT.top + (ClientRECT.right / 2 - 50) + 82;

	// 그라데이션의 끝색상를 명시한다.
	vert[0].Red = GetRValue(rgb) << 8;
	vert[0].Green = GetGValue(rgb) << 8;
	vert[0].Blue = GetBValue(rgb) << 8;
	vert[0].Alpha = 0xFFFF;

	vert[1].x = ClientRECT.right;
	vert[1].y = ClientRECT.bottom;

	// 그라데이션의 시작색상을 명시한다.
	vert[1].Red = 0xFFFFFF;
	vert[1].Green = 0xFFFFFF;
	vert[1].Blue = 0xFFFFFF;
	vert[1].Alpha = 0xFFFF;

	gtr.UpperLeft = 0;
	gtr.LowerRight = 1;

	GradientFill(memdc, vert, 2, &gtr, 1, GRADIENT_FILL_RECT_V);

	t.BlendOp = AC_SRC_OVER;
	t.BlendFlags = 0;
	t.SourceConstantAlpha = 200;
	t.AlphaFormat = 0;
	AlphaBlend(memdc, ClientRECT.left, ClientRECT.top + (ClientRECT.right / 2 - 50) + 82, ClientRECT.right, ClientRECT.bottom, uiDC, ClientRECT.left, ClientRECT.top + (ClientRECT.right / 2 - 50) + 82, ClientRECT.right, ClientRECT.bottom, t) ;

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Rectangle(memdc, ClientRECT.left, ClientRECT.top + 82 + (ClientRECT.right / 2 - 50), ClientRECT.right, ClientRECT.top + 85 + (ClientRECT.right / 2 - 50));

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
	DeleteDC(uiDC);
}