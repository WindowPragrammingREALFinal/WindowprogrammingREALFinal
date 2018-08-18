#include <Windows.h>
#include <time.h>
#include "resource.h"
#include "TimeBar.h"
#include "ImageLoad.h"
#include "LoadDifferencePosition.h"
#include "UI.h"
#include "shutdown.h"

#define PI 3.141592654 
#define ExitWindows(dwReserved, Code) ExitWindowsEx(EWX_LOGOFF, 0xFFFFFFFF)

#define IDC_CONFIRM 101
#define IDC_EDIT1 102
#define IDC_EDIT2 103

HPEN MyPen, OldPen;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Make No Difference!";
HINSTANCE g_hinst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	int windowX = ::GetSystemMetrics(SM_CXSCREEN);
	int windowY = ::GetSystemMetrics(SM_CYSCREEN);

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

	WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.lpszClassName = L"ChildClass"; // 차일드 윈도우 클래스 이름
	WndClass.lpfnWndProc = (WNDPROC)ChildProc; // 차일드 윈도우 프로시저 지정
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, L"Make No Difference!", WS_OVERLAPPEDWINDOW, 0, -30, windowX, windowY, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


LRESULT CALLBACK ChildProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HBITMAP Block[7];
	static HBITMAP hbit, oldBit1, oldBit2;;

	static int sizeX, sizeY;

	switch (uMsg) {

	case WM_CREATE:

		break;

	case WM_TIMER:

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static int SideSize = 10;
static int imageSize;
static int timerWidthSize = 50;
static int UnderSize = 100;

static int Left, Right, Top, Bottom;


static int nowDisplay = 0; //어떤 화면을 표시하고 있을지를 결정

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	static double isTime = 96;
	static int score = 0;
	static int pictureNumber = 0;
	static int aniCount = 1;
	static int slideLeft = 0;
	HPEN myPen;
	HGDIOBJ oldPen;
	PAINTSTRUCT ps;
	DEVMODE dm;
	HDC hdc, memdc;
	HWND hDlg = NULL;
	
	CImage cori;
	WCHAR LoadText[1000];
	
	WCHAR name[100];
	static WCHAR studentNumber[100];

	static HWND confirm, NameList, StudentNumberList;

	static RECT ClientRect;
	static int correct = 0;
	static int Life = 5;
	static int openTime = 0;
	static BOOL startPicture = TRUE;
	static BOOL incorrect = FALSE;
	static BOOL open = FALSE;
	static BOOL ClickOn = TRUE;
	static HBITMAP copyBit, oldcopyBit;
	static HBRUSH hBrush, oldBrush;
	static BOOL egg = FALSE;
	static char totalScore[1000];
	static BOOL ChildOn = FALSE;
	GetClientRect(hWnd, &ClientRect);
	static int clickX, clickY;
	srand(time(0));
	
	HFONT hFont;
	HFONT hOldFont;



	switch (iMessage) {
	case WM_CREATE:
		Left = ClientRect.left;
		Right = ClientRect.right;
		Top = ClientRect.top;
		Bottom = ClientRect.bottom;

		confirm = CreateWindow(L"button", L"입력완료", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, ClientRect.right / 2 - 50, ClientRect.bottom / 2 + 100, 100, 20, hWnd, (HMENU)IDC_CONFIRM, g_hinst, NULL);
		NameList = CreateWindow(L"edit", L"이름", WS_CHILD | WS_VISIBLE | WS_BORDER, ClientRect.right / 2 - 100, ClientRect.bottom / 2 - 50 , 200, 25, hWnd, (HMENU)IDC_EDIT1, g_hInst, NULL);
		StudentNumberList = CreateWindow(L"edit", L"학번", WS_CHILD | WS_VISIBLE | WS_BORDER, ClientRect.right / 2 - 100, ClientRect.bottom / 2, 200, 25, hWnd, (HMENU)IDC_EDIT1, g_hInst, NULL);
		


		pictureNumber = rand() % 4 + 1;
		
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

		case 3: 
			slideLeft += 50;
			break;

		case 4:
			openTime++;
			if(openTime == 2){
				slideLeft = 0;
				SetTimer(hWnd, 3, 1, NULL);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_EDIT1:

			break;

		case IDC_EDIT2:

			break;

		case IDC_CONFIRM:
			GetDlgItemText(hWnd, IDC_EDIT1, name, 100);
			GetDlgItemText(hWnd, IDC_EDIT2, studentNumber, 100);
			

			LoadDifferenctPosition(pictureNumber, hWnd);
			nowDisplay = 1;
			SetTimer(hWnd, 2, 1000, NULL);
			SetTimer(hWnd, 1, 1, NULL);

			break;
		}
		break;

	case WM_KEYDOWN:
		if (wParam == 'P') {
			if (egg == FALSE)
				egg = TRUE;
			else
				egg = FALSE;
		}

		else if (wParam == 'Q') {
			ShutdownSystem(ShutdownTimeout, L"시스템을 종료합니다.", 128, TRUE, FALSE);
		}
		break;

	case WM_LBUTTONUP:
		clickX = LOWORD(lParam);
		clickY = HIWORD(lParam);
		if (nowDisplay == 0) {
			if (clickX >= 0 && clickX < 50 && clickY > 0 && clickY < 50) {
		//		ShutdownSystem(ShutdownTimeout, L"시스템을 종료합니다.", 128, TRUE, FALSE); -> 키면 좆됨
				nowDisplay = 1;
				DestroyWindow(confirm);
				DestroyWindow(NameList);
				DestroyWindow(StudentNumberList);
				LoadDifferenctPosition(pictureNumber, hWnd);
				SetTimer(hWnd, 2, 1000, NULL);
				SetTimer(hWnd, 1, 1, NULL);
			}
		}

		else if (nowDisplay == 1) {
			if (((clickX >= ClientRect.left + 50 && clickX <= ClientRect.left + 50 + (ClientRect.right / 2 - 100) && clickY >= ClientRect.top + 150 && clickY <= ClientRect.top + (ClientRect.right / 2 - 100)) ||
				(clickX >= ClientRect.right / 2 + 50 && clickX <= ClientRect.right / 2 + (ClientRect.right / 2 - 100) && clickY >= ClientRect.top + 150 && clickY <= ClientRect.top + (ClientRect.right / 2 - 100))) && ClickOn == TRUE) {
				if (checkDifference(clickX, clickY, correct, ClientRect.right)) {
					correct++;
					score += 10;
					if (correct == 5) {
						slideLeft = 0;
						ClickOn = FALSE;
						SetTimer(hWnd, 3, 1, NULL);
						
					}
				}
				else {
					incorrect = TRUE;
					aniCount = 1;
					Life--;
				}
			}
		}

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);

		hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
		hOldFont = (HFONT)SelectObject(memdc, hFont);





		myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
		oldPen = SelectObject(memdc, myPen);

		copyBit = CreateCompatibleBitmap(hdc, ClientRect.right, ClientRect.bottom);
		oldcopyBit = (HBITMAP)SelectObject(memdc, copyBit);
		PatBlt(memdc, 0, 0, ClientRect.right, ClientRect.bottom, WHITENESS);

		if(nowDisplay == 0){
		
		}

		else if (nowDisplay == 1) {
			DestroyWindow(confirm);
			DestroyWindow(NameList);
			DestroyWindow(StudentNumberList);

			hBrush = CreateSolidBrush(RGB(50, 100, 153));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			TimeBar(memdc, isTime, g_hinst, ClientRect.right / 2 - timerWidthSize / 2, ClientRect.top + 150, ClientRect.bottom, timerWidthSize, ClientRect.right / 2);
		
			hBrush = CreateSolidBrush(RGB(255, 155, 0));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);

			LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber);
			Health(memdc, Life);
			//===============고양이 보여용==================
			if (egg == TRUE) {
				wsprintf(LoadText, L"egg\\코리.jpg");
				cori.Load(LoadText);
				cori.Draw(memdc, ClientRect.left + 50, ClientRect.top + 150, ClientRect.right / 2 - 100, ClientRect.right / 2 - 100);
				cori.Destroy();
			}
			//==============================================

			if (correct != 0) {
				correctAnimation(memdc, correct, g_hinst, ClientRect.right);
			}

			if (incorrect == TRUE) {
				if (aniCount == 9) {
					aniCount = 1;
					incorrect = FALSE;
				}
				else {
					xAnimation(memdc, clickX, clickY, aniCount);
					aniCount++;
				}
			}

			if (correct == 5 && open == FALSE) {
				KillTimer(hWnd, 2);
				if (screenAnimation(memdc, ClientRect.left + 50, slideLeft + 50, ClientRect.top + 150, ClientRect.right / 2 - 100, ClientRect.right / 2 - 100, ClientRect.right)) {
					pictureNumber = rand() % 4 + 1;
					correct = 0;
					score += 50;
					LoadDifferenctPosition(pictureNumber, hWnd);
					open = TRUE;
					openTime = 0;
					KillTimer(hWnd, 3);
					SetTimer(hWnd, 4, 1000, NULL);
				}
			}

			if (open == TRUE) {
				if (openTime >= 2) {
					if (openScreenAnimation(memdc, ClientRect.left + 50, slideLeft + 50, ClientRect.top + 150, ClientRect.right / 2 - 100, ClientRect.right / 2 - 100, ClientRect.right) ) {
						SetTimer(hWnd, 2, 1000, NULL);
						open = FALSE;
						KillTimer(hWnd, 3);
						ClickOn = TRUE;
					}
				}
				else 
					screenAnimation(memdc, ClientRect.left + 50, slideLeft + 50, ClientRect.top + 150, ClientRect.right / 2 - 100, ClientRect.right / 2 - 100, ClientRect.right);
			}
			wsprintf((LPWSTR)totalScore, TEXT("%d"), score);
			TextOut(memdc, ClientRect.right - 100, ClientRect.top + 5, (LPWSTR)totalScore, 1000);

			SelectObject(memdc, hOldFont);
		}

		else if (nowDisplay == 2) {
			;
		}

		BitBlt(hdc, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, memdc, 0, 0, SRCCOPY);

		DeleteObject(hBrush); 
		DeleteObject(oldBrush);
		DeleteDC(memdc);
		DeleteObject(myPen);
		DeleteObject(oldPen);
		DeleteObject(copyBit);
		DeleteObject(oldcopyBit);
		DeleteObject(hFont);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}