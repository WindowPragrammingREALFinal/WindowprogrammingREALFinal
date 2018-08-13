#include <Windows.h>
#include <time.h>
#include "resource.h"
#include "TimeBar.h"
#include "ImageLoad.h"
#include "LoadDifferencePosition.h"
#include "UI.h"
#define PI 3.141592654 

HPEN MyPen, OldPen;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Make No Difference!";
HINSTANCE g_hinst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


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
	hWnd = CreateWindow(lpszClass, L"Make No Difference!", WS_OVERLAPPEDWINDOW, 0, -30, windowX, windowY, NULL, (HMENU)NULL, hInstance, NULL);

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

	GetClientRect(hWnd, &ClientRect);
	static int clickX, clickY;
	srand(time(0));

	switch (iMessage) {
	case WM_CREATE:
		Left = ClientRect.left;
		Right = ClientRect.right;
		Top = ClientRect.top;
		Bottom = ClientRect.bottom;

		pictureNumber = rand() % 4 + 1;
		SetTimer(hWnd, 1, 1, NULL);
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
			if(openTime == 3){
				slideLeft = 0;
				SetTimer(hWnd, 3, 1, NULL);
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		

		break;

	case WM_LBUTTONUP:
		clickX = LOWORD(lParam);
		clickY = HIWORD(lParam);
		if (nowDisplay == 0) {
			if (clickX >= 0 && clickX < 50 && clickY > 0 && clickY < 50) {
				nowDisplay = 1;
				LoadDifferenctPosition(pictureNumber, hWnd);
				SetTimer(hWnd, 2, 1000, NULL);
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

		myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
		oldPen = SelectObject(memdc, myPen);

		copyBit = CreateCompatibleBitmap(hdc, ClientRect.right, ClientRect.bottom);
		oldcopyBit = (HBITMAP)SelectObject(memdc, copyBit);
		PatBlt(memdc, 0, 0, ClientRect.right, ClientRect.bottom, WHITENESS);

		if(nowDisplay == 0){
			;
		}

		else if (nowDisplay == 1) {
			
			hBrush = CreateSolidBrush(RGB(50, 100, 153));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			TimeBar(memdc, isTime, g_hinst, ClientRect.right / 2 - timerWidthSize / 2, ClientRect.top + 150, ClientRect.bottom, timerWidthSize);
		
			LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber);
			Health(memdc, Life);
	
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
				if (openTime > 2) {
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
		
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}