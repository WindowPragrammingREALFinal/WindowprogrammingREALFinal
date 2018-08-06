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
	HDC sourceDC = CreateCompatibleDC(hdc);                                      // ȸ���� ��Ʈ�� ������ ������ DC   
	HDC destDC = CreateCompatibleDC(hdc);                                      // ȸ���� ��Ʈ���� ��¹��� DC   
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, dest_width, dest_height);       // ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� �ڵ�   

	HBITMAP hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);                   // ȸ���� ��Ʈ�� ������ DC�� ����   
	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);                   // ȸ���� ��Ʈ���� ��¹��� DC��, ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� ����   

	HBRUSH hbrBack = CreateSolidBrush(bkColor);                                  // ȸ������ ����, ���鿵���� ĥ�� �귯���ڵ� ����   
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);                      // �귯���ڵ� ����   
	PatBlt(destDC, 0, 0, dest_width, dest_height, PATCOPY);                           // ���õ� �귯�÷�, ȸ���� ��Ʈ���� ��¹��� DC��, �̸� ������ ä�� ����   
	DeleteObject(SelectObject(destDC, hbrOld));                                     // �귯�� ����   

	angle = (float)(angle * PI / 180);                                      // ȸ���� ����(360�й�)��, ���ȴ����� ������ ����   
	float cosine = (float)cos(angle);                                              // ȸ���̵���ȯ ��Ŀ� �� cos��Ÿ ���� ����          
	float sine = (float)sin(angle);                                              // ȸ���̵���ȯ ��Ŀ� �� sin��Ÿ ���� ����   
	SetGraphicsMode(destDC, GM_ADVANCED);                                               // ������ ��ǥ���� ȸ���� ���Ͽ�, �׷��ȸ�带 Ȯ����� ����



	XFORM xform;                                                                        // �������� ǥ���ϴ� 3��3���� ��� ����   
	xform.eM11 = cosine;                                                                // 1�� 1�� ���� ���� (ȸ������)   
	xform.eM12 = sine;                                                                  // 1�� 2�� ���� ���� (ȸ������)   
	xform.eM21 = -sine;                                                                 // 2�� 1�� ���� ���� (ȸ������)   
	xform.eM22 = cosine;                                                                // 2�� 2�� ���� ���� (ȸ������)   
	xform.eDx = (FLOAT)dest_width / 2.0f;                                               // 3�� 1�� ���� ���� (X�� �̵� ����)   
	xform.eDy = (FLOAT)dest_height / 2.0f;                                              // 3�� 2�� ���� ���� (Y�� �̵� ����)   
																						// ������ ��ķ�, �μ�DC�� �������� ��ǥ�踦 ��ȯ.   
																						// �μ�DC�� ��´������ �޸𸮺�Ʈ���� �����Ƿ�,
																						// �����ϰ� �ִ� �޸𸮺�Ʈ���� ��ǥü�谡 ȸ���ȴ�.   
	SetWorldTransform(destDC, &xform);
	// ȸ���� �޸�DC��, ȸ���� �̹����� ���   
	BitBlt(destDC, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, sourceDC, source_x, source_y, SRCCOPY);
	// ���� �ڿ� ����   
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);
	DeleteObject(sourceDC);
	DeleteObject(destDC);
	// ȸ���� ��Ʈ�� �ڵ� ����   
	return hbmResult;
}



void RotateBlt(HDC hdc, HDC hOffScreen, int dest_x, int dest_y, int dest_width, int dest_height,
	HBITMAP hBit, int source_x, int source_y, DWORD dFlag, float angle, COLORREF bkColor)
{
	static HDC hTempMemDC;              // ȸ���� ��Ʈ���� ������ �޸�DC   
	HBITMAP hTempBitmap, hOldBitmap;    // ȸ���� ��Ʈ���� ������, ��Ʈ�� �ڵ�   
										// ���� �ѹ��� ��Ʈ��DC�� �����մϴ�.   
	if (!hTempMemDC) hTempMemDC = CreateCompatibleDC(hdc);
	// ��Ʈ���� ȸ���ϴ� �Լ��� ȣ���Ͽ�, ���ϵǴ� ȸ���� ��Ʈ�� �ڵ��� ����   
	hTempBitmap = GetRotatedBitmap(hdc, hBit, source_x, source_y, dest_width, dest_height, angle, bkColor);
	// ȸ���� ��Ʈ�� �ڵ��� �����ϰ�,
	hOldBitmap = (HBITMAP)SelectObject(hTempMemDC, hTempBitmap);
	// ������ũ��DC��, ȸ���� ��Ʈ�� �ڵ��� ������, �޸�DC�� �̹����� ����մϴ�.   
	// ���� �ּ��� �����ϸ�, �����ǥ�� �߽����� �ϴ� ȸ���̹����� �˴ϴ�.   
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


static int nowDisplay = 0; //� ȭ���� ǥ���ϰ� �������� ����

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

		case 3: // ȭ����ȯ �����

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
			; // �ΰ��� Ui OR Ʋ���׸� ã��ÿ� �����
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

			if (clickX > 1550 && clickY < 50)// ȭ����ȯ �����
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