#include <Windows.h>
#include <iostream>
#include <time.h>
#include "resource.h"
#include "TimeBar.h"
#include "ImageLoad.h"
#include "LoadDifferencePosition.h"
#define PI 3.141592654 
#define Height 1600
#define Weight 900

using namespace std;
HPEN MyPen, OldPen;
#define MAX 9
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Make No Difference!";
HINSTANCE g_hinst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

  
HBITMAP GetRotatedBitmap(HDC hdc, HBITMAP hBitmap, int source_x, int source_y, int dest_width, int dest_height, float angle, COLORREF bkColor)
{
	HDC sourceDC = CreateCompatibleDC(hdc);                                      // 회전할 비트맵 원본을 선택할 DC   
	HDC destDC = CreateCompatibleDC(hdc);                                      // 회전할 비트맵을 출력받을 DC   
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, dest_width, dest_height);       // 회전할 비트맵을 출력받을 메모리비트맵 핸들   

	HBITMAP hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);                   // 회전할 비트맵 원본을 DC에 선택   
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);                   // 회전할 비트맵을 출력받을 DC에, 회전할 비트맵을 출력받을 메모리비트맵 선택   

	HBRUSH hbrBack = CreateSolidBrush(bkColor);                                  // 회전으로 인한, 공백영역을 칠할 브러시핸들 생성   
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);                      // 브러시핸들 선택   
	PatBlt(destDC, 0, 0, dest_width, dest_height, PATCOPY);                           // 선택된 브러시로, 회전할 비트맵을 출력받을 DC에, 미리 색상을 채워 지움   
	DeleteObject(SelectObject(destDC, hbrOld));                                     // 브러시 해제   

	angle = (float)(angle * PI / 180);                                      // 회전할 각도(360분법)를, 라디안단위의 각도로 변경   
	float cosine = (float)cos(angle);                                              // 회전이동변환 행렬에 들어갈 cos세타 값을 구함          
	float sine = (float)sin(angle);                                              // 회전이동변환 행렬에 들어갈 sin세타 값을 구함   
	SetGraphicsMode(destDC, GM_ADVANCED);                                               // 윈도우 좌표계의 회전을 위하여, 그래픽모드를 확장모드로 변경



	XFORM xform;                                                                        // 방정식을 표현하는 3행3열의 행렬 선언   
	xform.eM11 = cosine;                                                                // 1행 1열 성분 설정 (회전성분)   
	xform.eM12 = sine;                                                                  // 1행 2열 성분 설정 (회전성분)   
	xform.eM21 = -sine;                                                                 // 2행 1열 성분 설정 (회전성분)   
	xform.eM22 = cosine;                                                                // 2행 2열 성분 설정 (회전성분)   
	xform.eDx = (FLOAT)dest_width / 2.0f;                                               // 3행 1열 성분 설정 (X축 이동 성분)   
	xform.eDy = (FLOAT)dest_height / 2.0f;                                              // 3행 2열 성분 설정 (Y축 이동 성분)   
																						// 설정한 행렬로, 인수DC의 윈도우즈 좌표계를 변환.   
																						// 인수DC는 출력대상으로 메모리비트맵을 가지므로,
																						// 선택하고 있는 메모리비트맵의 좌표체계가 회전된다.   
	SetWorldTransform(destDC, &xform);
	// 회전된 메모리DC에, 회전할 이미지를 출력   
	BitBlt(destDC, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, sourceDC, source_x, source_y, SRCCOPY);
	// 사용된 자원 해제   
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteObject(sourceDC);
	DeleteObject(destDC);
	// 회전된 비트맵 핸들 리턴   
	return hbmResult;
}



void RotateBlt(HDC hdc, HDC hOffScreen, int dest_x, int dest_y, int dest_width, int dest_height,
	HBITMAP hBit, int source_x, int source_y, DWORD dFlag, float angle, COLORREF bkColor)
{
	static HDC hTempMemDC;              // 회전한 비트맵을 선택할 메모리DC   
	HBITMAP hTempBitmap, hOldBitmap;    // 회전한 비트맵을 저장할, 비트맵 핸들   
										// 최초 한번만 비트맵DC를 생성합니다.   
	if (!hTempMemDC) hTempMemDC = CreateCompatibleDC(hdc);
	// 비트맵을 회전하는 함수를 호출하여, 리턴되는 회전된 비트맵 핸들을 저장   
	hTempBitmap = GetRotatedBitmap(hdc, hBit, source_x, source_y, dest_width, dest_height, angle, bkColor);
	// 회전된 비트맵 핸들을 선택하고,
	hOldBitmap = (HBITMAP)SelectObject(hTempMemDC, hTempBitmap);
	// 오프스크린DC에, 회전된 비트맵 핸들을 선택한, 메모리DC의 이미지를 출력합니다.   
	// 안의 주석을 해제하면, 출력좌표를 중심으로 하는 회전이미지가 됩니다.   
	StretchBlt(hOffScreen, dest_x/* - dest_width/2*/, dest_y/* - dest_height/2*/, dest_width, dest_height, hTempMemDC, 0, 0, dest_width, dest_height, RGB(255, 255, 255));
	SelectObject(hTempMemDC, hOldBitmap);
	DeleteObject(hTempBitmap);
}


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
	static int Life = 3;
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
			//InvalidateRect(hWnd, NULL, FALSE);
			break;

		case 3: // 화면전환 시험용

			break;
		}
		break;

	case WM_LBUTTONDOWN:
		if (nowDisplay == 0) {
			clickX = LOWORD(lParam);
			clickY = HIWORD(lParam);
			if (clickX >= 0 && clickX < 50 && clickY > 0 && clickY < 50) {
				nowDisplay = 1;
				SetTimer(hWnd, 2, 1000, NULL);
			}
		}
		else if (nowDisplay == 1) {
			; // 인게임 Ui OR 틀린그림 찾기시에 사용함
		}

		break;

	case WM_LBUTTONUP:
		clickX = LOWORD(lParam);
		clickY = HIWORD(lParam);

		if (nowDisplay == 1) {
			if (checkDifference(clickX, clickY, correct))
				correct++;
			else
				Life--;

			if (clickX > 1550 && clickY < 50)// 화면전환 시험용
				SetTimer(hWnd, 3, 10, NULL);
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
			PatBlt(memdc, 0, 0, ClientRect.right, ClientRect.bottom, WHITENESS);
			//StretchBlt(memdc, SideSize, SideSize, ClientRect.right - SideSize, ClientRect.bottom - SideSize, memdc, SideSize, SideSize, ClientRect.right - SideSize, ClientRect.bottom - SideSize, WHITENESS);
			hBrush = CreateSolidBrush(RGB(50, 100, 153));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			TimeBar(memdc, isTime, g_hinst, ClientRect.right / 2 - timerWidthSize / 2, ClientRect.top + 145, timerWidthSize);
		
			LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber);
			if (correct != 0) {
				correctAnimation(memdc, correct, g_hinst);
			}

			if (correct == 5) {
				pictureNumber = rand() % 3 + 1;
				correct = 0;
				LoadDifferenctPosition(pictureNumber, hWnd);
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