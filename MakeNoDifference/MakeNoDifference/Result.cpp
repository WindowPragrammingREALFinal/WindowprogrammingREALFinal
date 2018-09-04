#include "Result.h"

void Result(HDC memdc, int score, WCHAR name[], WCHAR studentNumber[], int slide, int score_digit,bool return_but_on,HWND hWnd) // 결과창 애니메이션도 있음
{
	
	RECT ClientRECT;
	HBRUSH hBrush, oldBrush;
	WCHAR LoadText[100];
	HFONT hFont,oldFont;
	int temp_score = score% (score_digit/10);
	GetClientRect(hWnd, &ClientRECT);

	RECT temp_rect = ClientRECT;
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
		SetTextColor(memdc, RGB(113, 203, 230));                                                                                   // 점수 RGB 조정
		hFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));        // 점수 폰트 조정
		oldFont = (HFONT)SelectObject(memdc, hFont);

		wsprintf(LoadText, L"%d", temp_score);
		DrawText(memdc, LoadText, wcslen(LoadText), &temp_rect, DT_CENTER || DT_VCENTER);

		DeleteObject(hFont);
		DeleteObject(oldFont);
	}

	if (score_digit >= 100000)
	{
		temp_rect.top = (ClientRECT.bottom / 5) * 3 + 20;                                                                       //학번,이름 위치 조정
		temp_rect.bottom = (ClientRECT.bottom / 5) * 4;

		SetTextColor(memdc, RGB(113, 203, 230));                                                                                // 학번,이름 RGB 조정
		hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));     // 학번,이름 폰트 조정
		oldFont = (HFONT)SelectObject(memdc, hFont);

		wsprintf(LoadText, L"%s / %s", name,studentNumber);
		DrawText(memdc, LoadText, wcslen(LoadText), &temp_rect, DT_CENTER || DT_VCENTER);

		DeleteObject(hFont);
		DeleteObject(oldFont);

		return_but_on = true;   //학번 이름까지 출력하면 뒤로가기 버튼 활성화
	}


	if (return_but_on == true)  //결과창 점수등 출력한 후 뒤로가기 버튼 on 되면
	{

		//뒤로가기 버튼 이미지 출력

	}
}


void saveData(int score, WCHAR name[100], WCHAR studentNumber[20])
{

	// 이곳이 혁수를 위한 장소 :)

	// 여기서 사용자 이름, 점수를 저장해주세요
}