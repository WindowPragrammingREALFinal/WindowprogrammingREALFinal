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

void remain(HDC memdc, int correct, HWND hWnd)
{
	RECT ClientRECT;
	static char difference[1000];
	GetClientRect(hWnd, &ClientRECT);
	HBRUSH hBrush, oldBrush;

	POINT left[3];
	POINT center[4];
	POINT right[3];

	center[0].x = ClientRECT.right / 2 - 50;
	center[0].y = ClientRECT.top + 52;
	center[1].x = ClientRECT.right / 2;
	center[1].y = ClientRECT.top + 2;
	center[2].x = ClientRECT.right / 2 + 50;
	center[2].y = ClientRECT.top + 52;
	center[3].x = ClientRECT.right / 2;
	center[3].y = ClientRECT.top + 102;

	left[0].x = ClientRECT.right / 2 - 100;
	left[0].y = ClientRECT.top;
	left[1].x = ClientRECT.right / 2 - 50;
	left[1].y = ClientRECT.top + 50;
	left[2].x = ClientRECT.right / 2 ;
	left[2].y = ClientRECT.top;

	right[0].x = ClientRECT.right / 2;
	right[0].y = ClientRECT.top;
	right[1].x = ClientRECT.right / 2 + 50;
	right[1].y = ClientRECT.top + 50;
	right[2].x = ClientRECT.right / 2 + 100;
	right[2].y = ClientRECT.top;

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, left, 3);
	
	hBrush = CreateSolidBrush(RGB(255, 155, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, center, 4);
	
	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
	Polygon(memdc, right, 3);

	wsprintf((LPWSTR)difference, TEXT("%d"), 5 - correct);
	SetBkColor(memdc, RGB(255, 155, 0));
	TextOut(memdc, ClientRECT.right / 2 - 15, ClientRECT.top + 30, (LPWSTR)difference ,1);

	DeleteObject(hBrush);
	DeleteObject(oldBrush);
}


void setting()
{
	// 폐기 예정
}

