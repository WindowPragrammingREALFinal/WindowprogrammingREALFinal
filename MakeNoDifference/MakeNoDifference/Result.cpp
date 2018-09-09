#include "Result.h"

CImage ScoreBG;
CImage restart;

void LoadScoreBG()
{
	WCHAR LoadText[1000];
	wsprintf(LoadText, L"Result_Button\\5.png");
	ScoreBG.Load(LoadText);
}


void DrawScoreBG(HDC memdc, HWND hWnd)
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);

	ScoreBG.Draw(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right, ClientRECT.bottom);
}

void ScoreBGDestroy()
{
	ScoreBG.Destroy();
}

void LoadRestartButton()
{
	WCHAR LoadText[1000];
	wsprintf(LoadText, L"Result_Button\\button.png");
	restart.Load(LoadText);
}

void DrawRestartButton(HDC memdc, HWND hWnd)
{
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);

	restart.Draw(memdc, 820, 760, 256, 256);
}

void DestroyRestartButton()
{
	restart.Destroy();
}


void Result(HDC memdc, int score, WCHAR name[], WCHAR studentNumber[], int slide, int score_digit, bool *return_but_on, HWND hWnd, COLORREF rgb) // ���â �ִϸ��̼ǵ� ����
{
	
	RECT ClientRECT;
	HBRUSH hBrush, oldBrush;
	WCHAR LoadText[100];
	HFONT hFont, oldFont;
	int temp_score = score % (score_digit / 10);
	GetClientRect(hWnd, &ClientRECT);



	RECT temp_rect = ClientRECT; // �ӽ� ��Ʈ(���� ��¿�)
	temp_rect.top = (ClientRECT.bottom / 5) * 2 + 70;
	temp_rect.bottom = (ClientRECT.bottom / 5) * 3;


	hBrush = CreateSolidBrush(RGB(113, 203, 230));
	oldBrush = (HBRUSH)SelectObject(memdc, hBrush);

	Rectangle(memdc, ClientRECT.left, (ClientRECT.bottom / 5) * 2, slide, (ClientRECT.bottom / 5) * 2 + 3);
	Rectangle(memdc, ClientRECT.right - slide, (ClientRECT.bottom / 5) * 3, ClientRECT.right, (ClientRECT.bottom / 5) * 3 + 3);
	
	DeleteObject(hBrush);
	DeleteObject(oldBrush);
	
	
	if (score_digit > 10)
	{
		SetTextColor(memdc, RGB(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb))); // ���� RGB ����
		hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�޸ո���T"));   // ���� ��Ʈ ����
		oldFont = (HFONT)SelectObject(memdc, hFont);

		SetBkMode(memdc, TRANSPARENT);
		wsprintf(LoadText, L"%d", temp_score);
		DrawText(memdc, LoadText, wcslen(LoadText), &temp_rect, DT_CENTER || DT_VCENTER);

		DeleteObject(hFont);
		DeleteObject(oldFont);
	}

	if (score_digit >= 100000)
	{
		temp_rect.top = (ClientRECT.bottom / 5) * 3 + 20;     //�й�,�̸� ��ġ ����
		temp_rect.bottom = (ClientRECT.bottom / 5) * 4;

		SetTextColor(memdc, RGB(113, 203, 230));      // �й�,�̸� RGB ����
		hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�޸ո���T"));     // �й�,�̸� ��Ʈ ����
		oldFont = (HFONT)SelectObject(memdc, hFont);

		SetBkMode(memdc, TRANSPARENT);
		wsprintf(LoadText, L"%s / %s", name,studentNumber);
		DrawText(memdc, LoadText, wcslen(LoadText), &temp_rect, DT_CENTER || DT_VCENTER);
		DrawRestartButton(memdc, hWnd);
		DeleteObject(hFont);
		DeleteObject(oldFont);

		*return_but_on = true;   //�й� �̸����� ����ϸ� �ڷΰ��� ��ư Ȱ��ȭ
	}


	if (*return_but_on == true)  //���â ������ ����� �� �ڷΰ��� ��ư on �Ǹ�
	{

		//�ڷΰ��� ��ư �̹��� ���

	}
}


void saveData(int score, WCHAR name[100], WCHAR studentNumber[20])
{

	// �̰��� ������ ���� ��� :)

	// ���⼭ ����� �̸�, ������ �������ּ���
}