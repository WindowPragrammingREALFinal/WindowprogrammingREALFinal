#include "login.h"
#include <Windows.h>
#include <atlImage.h>

void LoginScreen(HDC memdc, int nowImage, HWND hWnd) //로그인 창 뜨기전 타이틀 화면
{
	CImage login;
	WCHAR LoadText[1000];
	RECT ClientRECT;
	GetClientRect(hWnd, &ClientRECT);
	   
	wsprintf(LoadText, L"Title\\TITLE_%d.png", nowImage, nowImage);
	login.Load(LoadText);
	login.Draw(memdc, ClientRECT.left, ClientRECT.top, ClientRECT.right, ClientRECT.bottom);
	login.Destroy();
}

 void UserDataSave(TCHAR name[1000], int number) // 폐기 예정
{

}