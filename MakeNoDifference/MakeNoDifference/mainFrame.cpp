#include <Windows.h>
#include <iostream>
#include <time.h>
#include "resource.h"
#include "TimeBar.h"
#include "ImageLoad.h"

#define Height 1920
#define Weight 1080

using namespace std;
HPEN MyPen, OldPen;
#define MAX 9
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Make No Difference!";
HINSTANCE g_hinst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, L"Make No Difference!", WS_OVERLAPPEDWINDOW, 0, -30, Height, Weight, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

static int SideSize = 10;
static int imageSize;
static int timerWidthSize = 50;
static int UnderSize = 100;

static int Left, Right, Top, Bottom;

BOOL CALLBACK Dlg_1Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HWND hButton;
	PAINTSTRUCT d_ps;
	HBRUSH hBrush, oldBrush;
	//체크박스 용
	static int size;
	static int imagesize;
	static int timeWeight;
	static int under;
	char test[1000];
	char test2[1000];
	char test3[1000];
	switch (iMessage)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_OK:
			size = GetDlgItemInt(hDlg, ID_SIDESIZE, NULL, TRUE);
			imagesize = GetDlgItemInt(hDlg, ID_IMAGESIZE, NULL, TRUE);
			timeWeight = GetDlgItemInt(hDlg, ID_WEIGHT, NULL, TRUE);
			under = GetDlgItemInt(hDlg, ID_UNDERSIZE, NULL, TRUE);

			SideSize = size;
			imageSize = imagesize;
			timerWidthSize = timeWeight;
			UnderSize = under;

			InvalidateRect(hDlg, NULL, TRUE);
			break;

		case ID_TRAP:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hDlg, &d_ps);
		wsprintf((LPWSTR)test, TEXT("타이머 : 좌상단:(%d , %d),우하단:(%d , %d)   "), (Right / 2) - (timeWeight / 2), Top + 250, (Right / 2) + (timeWeight / 2), Top + 750);
		TextOut(hdc, 50, 190, (LPCWSTR)test, 38);

		wsprintf((LPWSTR)test2, TEXT("하단부 : 좌상단:(%d , %d),우하단:(%d , %d)   "), SideSize, Bottom - SideSize - UnderSize, Right - SideSize, Bottom - SideSize);
		TextOut(hdc, 50, 230, (LPCWSTR)test2, 39);
		
		EndPaint(hDlg, &d_ps);
		break;

	}
	return 0;
}

static int nowDisplay = 0; //어떤 화면을 표시하고 있을지를 결정

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	static int isTime;
	static int pictureNumber = 0;
	PAINTSTRUCT ps;
	DEVMODE dm;
	HDC hdc, memdc;
	HWND hDlg = NULL;

	static RECT ClientRect;
	static int correct = 0;
	static BOOL startPicture = TRUE;
	static HBITMAP copyBit, oldcopyBit;
	static HBRUSH hBrush, oldBrush;
	
	GetClientRect(hWnd, &ClientRect);
	static int clickX, clickY;
	srand(time(0));

	switch (iMessage) {
	case WM_CREATE:
		
		ZeroMemory(&dm, sizeof(DEVMODE));
		dm.dmSize = sizeof(DEVMODE);
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		dm.dmBitsPerPel = 16;
		dm.dmPelsWidth = ClientRect.bottom;
		dm.dmPelsHeight = ClientRect.right;

		Left = ClientRect.left;
		Right = ClientRect.right;
		Top = ClientRect.top;
		Bottom = ClientRect.bottom;

		if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			ChangeDisplaySettings(&dm, 0);
		isTime = 100;
		pictureNumber = rand() % 3 + 1;
		SetTimer(hWnd, 1, 10, NULL);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1:
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case 2:
			isTime -= 1;
			if (isTime == 0)
				KillTimer(hWnd, 2);
			break;

		}
		break;

	case WM_LBUTTONDOWN:
		clickX = LOWORD(lParam);
		clickY = HIWORD(lParam);

		if (nowDisplay == 0) {
			if (clickX >= 0 && clickX < 50 && clickY > 0 && clickY < 50) {
				nowDisplay = 1;
				//DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg_1Proc);
				hDlg = CreateDialog(g_hinst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg_1Proc);
				ShowWindow(hDlg, SW_SHOW);
				SetTimer(hWnd, 2, 1000, NULL);
			}
		}
		else if (nowDisplay == 1) {
			; // 인게임 Ui OR 틀린그림 찾기시에 사용함
		}

		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);

		if(nowDisplay == 0){
			;
		}

		else if (nowDisplay == 1) {
			copyBit = CreateCompatibleBitmap(hdc, ClientRect.right, ClientRect.bottom);
			oldcopyBit = (HBITMAP)SelectObject(memdc, copyBit);

			StretchBlt(memdc, SideSize, SideSize, ClientRect.right - SideSize, ClientRect.bottom - SideSize, memdc, SideSize, SideSize, ClientRect.right - SideSize, ClientRect.bottom - SideSize, WHITENESS);
			hBrush = CreateSolidBrush(RGB(50, 100, 153));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			TimeBar(memdc, isTime, g_hinst, ClientRect.right / 2 - timerWidthSize / 2, ClientRect.top + 250, timerWidthSize);


			hBrush = CreateSolidBrush(RGB(10, 255, 255));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			Rectangle(memdc, SideSize, ClientRect.bottom - SideSize - UnderSize, ClientRect.right - SideSize, ClientRect.bottom - SideSize);
			LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber);
			if (correct == 5) {
				pictureNumber = rand() % 3 + 1;
				correct = 0;
			}
		}

		else if (nowDisplay == 2) {
			;
		}

		BitBlt(hdc, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, memdc, 0, 0, SRCCOPY);

		DeleteDC(memdc);
		DeleteObject(copyBit);
		DeleteObject(oldcopyBit);
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}