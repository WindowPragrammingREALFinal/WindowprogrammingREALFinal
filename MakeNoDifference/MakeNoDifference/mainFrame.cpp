#include <Windows.h>
#include <iostream>
#include <time.h>
#include "resource.h"
#include "login.h"
#include "TimeBar.h"
#include "ImageLoad.h"
#include "LoadDifferencePosition.h"
#include "UI.h"
#include "shutdown.h"
#include "Result.h"
#include "NextPicture.h"


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


static int windowX;
static int windowY;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	windowX = ::GetSystemMetrics(SM_CXSCREEN);
	windowY = ::GetSystemMetrics(SM_CYSCREEN);

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


	hWnd = CreateWindow(lpszClass, L"Make No Difference!", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, -30, windowX, windowY, NULL, (HMENU)NULL, hInstance, NULL);

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

struct timeBarRGB {
	int r = 0;
	int g = 136;
	int b = 187;

	BOOL Rbool = FALSE;
	BOOL Gbool = FALSE;
	BOOL Bbool = FALSE;
};

struct bottomBarRGB {
	int r = 192;
	int g = 192;
	int b = 192;

	int count = 0;

	BOOL check = TRUE;
};

struct remainRGB {
	int r = 255;
	int g = 255;
	int b = 255;
	int count = 0;
	BOOL check = TRUE;
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) 
{
	static double isTime = 96;
	static int score = 0;
	static int pictureNumber = 0;
	static int differenceNum = 0;
	static int aniCount = 1;
	static int slideLeft = 0;
	static int temp_score = 0;
	static int startSlideY;
	static int startSlideX;
	static int healthAnimation = 0; // 하트 터질때 애니메이션
	static int correct = 0;
	static int Life = 5;
	static int openTime = 0;
	static BOOL startSlideCheck = FALSE;
	static int scoreAnimationCount = 0;
	static BOOL scoreOn = FALSE;
	static BOOL startPicture = TRUE;
	static BOOL incorrect = FALSE;
	static BOOL startButton = FALSE;
	static BOOL open = FALSE;
	static BOOL ClickOn = TRUE;
	static BOOL bottomOn = FALSE;
	static BOOL load = TRUE;
	static BOOL scoreAnimation = FALSE;
	static BOOL wcCheck = FALSE;
	static double acc = 1;
	static BOOL chil = FALSE;
	static BOOL sideOn = FALSE;
	static BOOL changeOn = FALSE;
	static int nowCount = 0;

	static int moveX = 0;
	static int tempMoveX = 0;
	static int temp = 0;
	static BOOL moveSquare = FALSE;


	static COLORREF timeRGB;
	static timeBarRGB rgb;
	
	static COLORREF bottomRGB;
	static remainRGB brgb;
	static COLORREF scoreRGB;
	static timeBarRGB sc;

	static HPEN myPen;
	static HGDIOBJ oldPen;
	PAINTSTRUCT ps;
	static HDC hdc, memdc;
	static HWND hDlg = NULL;

	static WCHAR name[100];
	static WCHAR studentNumber[100];

	static HWND confirm, NameList, StudentNumberList;

	static RECT ClientRect;
	


	static BOOL egg = FALSE;
	static char totalScore[1000];
	static BOOL ChildOn = FALSE;
	GetClientRect(hWnd, &ClientRect);
	static int clickX, clickY;
	srand(time(0));
	
	static COLORREF loginRGB;
	static HFONT hFont;
	static HFONT hOldFont;
	static HBITMAP hBitmap, hbmMemOld;
	static HBRUSH hBrush, oldBrush;

	//result.cpp에서 이용
	static int score_digit = 10;
	static bool return_but_on = false;
	static bool is_resultbg_ani_on = true;
	static int resultbg_time = 0; //알파블랜드 속도

	switch (iMessage) {
	case WM_CREATE:
		Left = ClientRect.left;
		Right = ClientRect.right;
		Top = ClientRect.top;
		Bottom = ClientRect.bottom;

		startSlideY = ClientRect.bottom / 2;
		startSlideX = ClientRect.right / 2;

		BGLoad();
		bottomBarLoad();
		LoadBack();
		TempLoad();

		SetTimer(hWnd, 1, 1, NULL);
		SetTimer(hWnd, 5, 1, NULL);
		
		//pictureNumber = rand() % 16 + 1;
		pictureNumber = nextNumber();
		differenceNum = differenceNumber(pictureNumber);
		break;

	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (nowDisplay == 1) {
				timeRGB = RGB(rgb.r, rgb.g, rgb.b);
				if (moveSquare == TRUE) {
					if (moveX <= 100)
						moveX++;
				}
				else {
					if (moveX >= 0)
						moveX--;
				}
				if (temp_score < score)
					temp_score++;

				if (bottomOn == TRUE) {
					if (brgb.check == TRUE) {
						if (brgb.count < 6) {
							brgb.r -= 35;
							brgb.g -= 24;
							brgb.b -= 15;
							brgb.count++;
						}
						else if (brgb.count >= 6 && brgb.count < 12) {
							brgb.r += 35;
							brgb.g += 24;
							brgb.b += 15;
							brgb.count++;
						}
						else {
							bottomOn = FALSE;
							brgb.count = 0;
						}
					}
					else {
						if (brgb.count < 6) {
							//brgb.r += 25;
							brgb.g -= 23;
							brgb.b -= 26;
							brgb.count++;
						}
						else if (brgb.count >= 6 && brgb.count < 12) {
							//brgb.r -= 25;
							brgb.g += 23;
							brgb.b += 26;
							brgb.count++;
						}
						else {
							bottomOn = FALSE;
							brgb.count = 0;
						}
					}
				}

				bottomRGB = RGB(brgb.r, brgb.g, brgb.b);
			}
			else if (nowDisplay == 2) {
				if (is_resultbg_ani_on == true)
				{
					//결과창 배경 알파블랜드 속도 조정
					if (resultbg_time == 250)
						resultbg_time = 255;
					else
						resultbg_time += 2;
					

					
					if (resultbg_time == 255)
						is_resultbg_ani_on = false;
				}
				else if (slideLeft < ClientRect.right) {
					slideLeft += acc * isTime;
					isTime++;
				}
				else
				{
					static int temp_time = 1;
					temp_time++;

					if ((temp_time % 30 == 0) && (score_digit < 1000000))
					{
						if (score_digit != 1000000)
							score_digit = score_digit * 10;
						temp_time = 1;
					}
				}

				if (sc.Rbool == FALSE) {
					sc.r += 7;
					if (sc.r >= 255 - 9)
						sc.Rbool = TRUE;
				}
				else if (sc.Rbool == TRUE) {
					sc.r -= 7;
					if (sc.r <= 9)
						sc.Rbool = FALSE;
				}

				if (sc.Gbool == FALSE) {
					sc.g += 3;
					if (sc.g >= 255 - 5)
						sc.Gbool = TRUE;
				}
				else if (sc.Gbool == TRUE) {
					sc.g -= 3;
					if (sc.g <= 5)
						sc.Gbool = FALSE;
				}

				if (sc.Bbool == FALSE) {
					sc.b += 5;
					if (sc.b >= 255 - 7)
						sc.Bbool = TRUE;
				}
				else if (sc.Bbool == TRUE) {
					sc.b -= 5;
					if (sc.b <= 7)
						sc.Bbool = FALSE;
				}
			}
			scoreRGB = RGB(sc.r, sc.g, sc.b);

			if (startSlideCheck == TRUE) {
				if (startSlideY > 0)
					startSlideY -= 10;
				else if(startSlideY <= 0)
					startSlideY = 0;

				if (startSlideX > 0)
					startSlideX -= 20;
				else if (startSlideX <= 0)
					startSlideX = 0;

				if (startSlideX == 0 && startSlideY == 0)
					sideOn = TRUE;
			}

			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case 2:
			SetTimerGradation(isTime, ClientRect.right / 2, hWnd);
			rgb.r += 2;
	/*		if(rgb.g - 107 > 0)
				rgb.g -= 1;*/
			if(rgb.b - 140 > 0)
				rgb.b -= 1;
			
			if (isTime > 0)
				isTime -= 1;

			if (isTime == 0) {
				nowDisplay = 2;
				slideLeft = 0;
				isTime = 0;
				LoadRestartButton();
				LoadScoreBG();
				SetTimer(hWnd, 6, 100, NULL);
				saveData(score, name, studentNumber);
				KillTimer(hWnd, 2);
			}
			break;

		case 3: 
			slideLeft += 50;
			break;

		case 4:
			openTime++;
			if(openTime == 2){
				slideLeft = 0;
				SetTimer(hWnd, 3, 1, NULL);
			}
			break;

		case 5:
			if (nowCount < 89)
				nowCount++;
			else
				KillTimer(hWnd, 5);
			break;

		case 6:
			if(scoreAnimationCount < 6)
				scoreAnimationCount++;
			else {
				scoreOn = FALSE;
				scoreAnimationCount = 0;
				KillTimer(hWnd, 6);
			}
			break;
		case 7:  // 하트 터지는 애니메이션
		{
			healthAnimation++;
			if (healthAnimation == 10) {
				healthAnimation = 0;
				KillTimer(hWnd, 7);
			}

			break;
		}

		case 8:
			if (nowDisplay == 3) {
				if (tempMoveX < 1080) {
					tempMoveX += temp;
					temp += 5;
				}
				else {
					temp = 0;
					ChildOn = TRUE;
					KillTimer(hWnd, 8);
				}
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		

		break;

	case WM_MOUSEMOVE:
		if (nowDisplay == 0) {
			clickX = LOWORD(lParam);
			clickY = HIWORD(lParam);
			if (clickX >= ClientRect.right / 2 - 100 && clickX <= ClientRect.right / 2 + 100 && clickY >= ClientRect.bottom / 2 + 250 && clickY <= ClientRect.bottom / 2 + 350) {
				if (moveSquare == FALSE) {
					moveSquare = TRUE;
				}
			}
			else
				moveSquare = FALSE;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_EDIT1:
/*			hFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));
			SendMessage(NameList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);
			SendMessage(StudentNumberList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE)*/;
		//	GetDlgItemText(hWnd, IDC_EDIT1, name, 100);
			break;

		case IDC_EDIT2:
			/*hFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));
			SendMessage(NameList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);
			SendMessage(StudentNumberList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);*/
		//	GetDlgItemText(hWnd, IDC_EDIT2, studentNumber, 100);

			break;

		case IDC_CONFIRM:
			GetDlgItemText(hWnd, IDC_EDIT1, name, 100);
			GetDlgItemText(hWnd, IDC_EDIT2, studentNumber, 100);
			
			LoadDifferenctPosition(pictureNumber, differenceNum, hWnd);
			nowDisplay = 1;
			SetTimer(hWnd, 2, 1000, NULL);

			break;

		
		}
		
		break;


	case WM_CTLCOLOREDIT:
		hFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));
		SendMessage(NameList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);
		SendMessage(StudentNumberList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);
		SetTextColor((HDC)wParam, RGB(113, 203, 230));
		SetTextColor((HDC)wParam, RGB(113, 203, 230));
		return (BOOL)(MyPen = CreatePen(PS_NULL, 0, RGB(113, 203, 230)));

		break;

	case WM_KEYDOWN:

		if (nowDisplay == 0) {
			nowDisplay = 3;
			SetTimer(hWnd, 8, 1, NULL);

		}
		
		else if (nowDisplay == 1) {
			if (wParam == VK_SPACE) {
				correct = 5;
				open = FALSE;
				slideLeft = 0;
				ClickOn = FALSE;
				SetTimer(hWnd, 3, 1, NULL);
			}
		}

		else if (nowDisplay == 3) {

		
		}
		break;

	case WM_CHAR:

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
				LoadDifferenctPosition(pictureNumber, differenceNum ,hWnd);
				load = TRUE;
				LoadCImagePicture(pictureNumber,differenceNum);
			//	LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber, load);
				SetTimer(hWnd, 2, 1000, NULL);
			}
		}

		else if (nowDisplay == 1) {
			if (((clickX >= ClientRect.left + 17 && clickX <= ClientRect.left + 17 + (ClientRect.right / 2 - 50) && clickY >= ClientRect.top + 82 && clickY <= ClientRect.top + 82 + (ClientRect.right / 2 - 50)) ||
				(clickX >= ClientRect.right / 2 + 33 && clickX <= ClientRect.right / 2 + 33 + (ClientRect.right / 2 - 50) && clickY >= ClientRect.top + 82 && clickY <= ClientRect.top + 82 + (ClientRect.right / 2 - 50))) && ClickOn == TRUE){
				if (checkDifference(clickX, clickY, correct, ClientRect.right)) {
					correct++;
					score += 10;
					brgb.r = 255;
					brgb.g = 255;
					brgb.b = 255;
					bottomOn = TRUE;
					scoreOn = TRUE;
					SetTimer(hWnd, 6, 1, NULL);
					brgb.check = TRUE;
					if (correct == 5) {
						slideLeft = 0;
						ClickOn = FALSE;
						SetTimer(hWnd, 3, 1, NULL);
						
					}
				}
				else {
					brgb.r = 255;
					brgb.g = 255;
					brgb.b = 255;
					bottomOn = TRUE;
					brgb.check = FALSE;
					incorrect = TRUE;
					aniCount = 1;
					Life--;
					SetTimer(hWnd, 7, 10, NULL);
					if (Life == 0) {
						nowDisplay = 2;
						slideLeft = 0;
						isTime = 0;
						LoadScoreBG();
						LoadRestartButton();
						SetTimer(hWnd, 6, 100, NULL);
						saveData(score, name, studentNumber);
						KillTimer(hWnd, 2);
					}
				}
			}
		}
		else if (nowDisplay == 2)
		{
			if (return_but_on == true)  
			{
				//(820, 760)
				if ((clickX > 820 && clickX < 820 + 256) && (clickY > 760 && clickY < 760 + 256)){   //뒤로가기 버튼 좌표
				     //버튼 클릭시 
					return_but_on = false;
					isTime = 96;
					resultbg_time = 0;
					rgb.r = 0;
					rgb.b = 136;
					rgb.b = 187;
					brgb.r = 255;
					brgb.g = 255;
					brgb.b = 255;
					score = 0;
					resultbg_time = 0;
					pictureNumber = 0;
					differenceNum = 0;
					aniCount = 1;
					slideLeft = 0;
					temp_score = 0;
					startSlideY = ClientRect.bottom / 2;
					startSlideX = ClientRect.right / 2;
					correct = 0;
					resetTemp();
					Life = 5;
					openTime = 0;
					score_digit = 10;
					tempMoveX = 0;
					startSlideCheck = FALSE;
					scoreAnimationCount = 0;
					scoreOn = FALSE;
					startPicture = TRUE;
					incorrect = FALSE;
					startButton = FALSE;
					is_resultbg_ani_on = true;
					open = FALSE;
					ClickOn = TRUE;
					sideOn = FALSE;
					bottomOn = FALSE;
					load = TRUE;
					scoreAnimation = FALSE;
					wcCheck = FALSE;
					acc = 1;
					chil = FALSE;
					nowCount = 0;
					moveX = 0;
					moveSquare = FALSE;
					DestoryCimage();
					DestroyRestartButton();
					ScoreBGDestroy();
					SetTimer(hWnd, 5, 1, NULL);
					nowDisplay = 0;
					clearMap();
					countReset();
					pictureNumber = nextNumber();
					differenceNum = differenceNumber(pictureNumber);
				}
			
			}
		}
		else if (nowDisplay == 3) {
			if ((clickX > 1543 && clickX < 1543 + 256) && (clickY > 396 && clickY < 396 + 256) && startButton == TRUE) {
				DestroyWindow(confirm);
				DestroyWindow(NameList);
				DestroyWindow(StudentNumberList);
				LoadDifferenctPosition(pictureNumber, differenceNum, hWnd);
				load = TRUE;
				LoadCImagePicture(pictureNumber, differenceNum);
				nowDisplay = 1;
				startSlideCheck = TRUE;
				BGDestroy();
				bottomBarDestroy();
				BGLoad();
				bottomBarLoad();
				//	LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber, load);
				SetTimer(hWnd, 2, 1000, NULL);
			}
		}

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
	//	SetTextAlign(memdc, TA_CENTER);
		
	
		myPen = CreatePen(PS_NULL, 0, RGB(255, 255, 255));
		oldPen = SelectObject(memdc, myPen);

		hBitmap = CreateCompatibleBitmap(hdc, ClientRect.right, ClientRect.bottom);
		hbmMemOld = (HBITMAP)SelectObject(memdc, hBitmap);
		SelectObject(memdc, (HBITMAP)hBitmap);
		
		hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 255, 255, 255, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼엑스포"));
		hOldFont = (HFONT)SelectObject(memdc, hFont);
		hBrush = CreateSolidBrush(RGB(192, 192, 192));
		oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
		Rectangle(memdc, 0, 0, 1923, 1083);
		if(nowDisplay == 0){
			//Start(memdc, moveX, hWnd);
			LoginScreen(memdc, nowCount, hWnd);
		}

		else if (nowDisplay == 1) {
			BGDraw(memdc, hWnd);
		
			hBrush = CreateSolidBrush(RGB(50, 100, 153));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			DeleteObject(oldBrush);
			DeleteObject(hBrush);
			TimeBar(memdc, isTime, g_hinst, ClientRect.right / 2 - timerWidthSize / 2, ClientRect.top + 150, ClientRect.bottom, timerWidthSize, ClientRect.right / 2, hWnd, timeRGB);
			hBrush = CreateSolidBrush(RGB(255, 155, 0));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			DeleteObject(oldBrush);
			DeleteObject(hBrush);
			LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber, load);
			load = FALSE;
		//	
	
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
			
			hBrush = CreateSolidBrush(RGB(255, 155, 0));
			oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
			DeleteObject(oldBrush);
			DeleteObject(hBrush);
			if (correct == 5 && open == FALSE) {
				KillTimer(hWnd, 2);
				if (screenAnimation(memdc, ClientRect.left + 17, slideLeft + 17, ClientRect.top + 82, ClientRect.right / 2 - 50, ClientRect.right / 2 - 50, ClientRect.right, hWnd)) {
					pictureNumber = nextNumber();
					differenceNum = differenceNumber(pictureNumber);
					correct = 0;
					score += 50;
					load = TRUE;
					DestoryCimage();
					LoadCImagePicture(pictureNumber,differenceNum);
					//LoadPicture(memdc, g_hinst, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, pictureNumber,load);
					
					load = FALSE;
					LoadDifferenctPosition(pictureNumber, differenceNum, hWnd);
					open = TRUE;
					openTime = 0;
					KillTimer(hWnd, 3);
					SetTimer(hWnd, 4, 1000, NULL);
				}
			}
			
			if (open == TRUE) {
				if (openTime >= 2) {
					if (openScreenAnimation(memdc, ClientRect.left + 17, slideLeft + 17, ClientRect.top + 82, ClientRect.right / 2 - 50, ClientRect.right / 2 - 50, ClientRect.right) ) {
						SetTimer(hWnd, 2, 1000, NULL);
						open = FALSE;
						KillTimer(hWnd, 3);
						ClickOn = TRUE;
					}
				}
				else 
					screenAnimation(memdc, ClientRect.left + 17, slideLeft + 17, ClientRect.top + 82, ClientRect.right / 2 - 50, ClientRect.right / 2 - 50, ClientRect.right, hWnd);
			}

			bottomBar(memdc, bottomRGB, hWnd);
			Health(memdc, Life, healthAnimation);
			nowStage(memdc, hWnd);
			InGameUserData(memdc, name, studentNumber, hWnd);
			HFONT hFont, oldFont;
			hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼모음T"));        // 점수 폰트 조정
			oldFont = (HFONT)SelectObject(memdc, hFont);
			remain(memdc, correct, hWnd, bottomRGB, startSlideY, startSlideX, open);
			if (sideOn == TRUE)
				;
			
			if(scoreOn == FALSE)
				scoreImage(memdc, hWnd, temp_score, 6);
			else if(scoreOn == TRUE)
				scoreImage(memdc, hWnd, temp_score, scoreAnimationCount);

		

			
		/*	WCHAR checkcheckcheckcheck[1000];
			wsprintf(checkcheckcheckcheck, L"%d", pictureNumber);
			TextOut(memdc, (ClientRect.left + ClientRect.right) / 2, (ClientRect.top + ClientRect.bottom) / 2, checkcheckcheckcheck, wcslen(checkcheckcheckcheck));*/

			DeleteObject(hFont);
			DeleteObject(oldFont);
		}

		//결과창
		else if (nowDisplay == 2) {
			DrawScoreBG(memdc, hWnd, resultbg_time);
			if (is_resultbg_ani_on == false)
				Result(memdc, score, name, studentNumber, slideLeft, score_digit, &return_but_on, hWnd, scoreRGB);

			int i = 0;
			
			if (is_resultbg_ani_on == true)
				i = 1;
			else
				i = 0;
			//WCHAR tt[1000];
			//wsprintf(tt, L"%d, %d", resultbg_time, i);
			//TextOut(memdc, 0, 0, tt,wcslen(tt));
			//WCHAR tt[1000];
			//wsprintf(tt, L"%d, %d", resultbg_time, i);
			//TextOut(memdc, 0, 0, tt,wcslen(tt));
		}

		else if (nowDisplay == 3) {
			hFont = CreateFont(400, 400, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 255, 255, 255, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼엑스포"));
			hOldFont = (HFONT)SelectObject(memdc, hFont);

			login(memdc, hWnd);
			TempDraw(memdc, tempMoveX, hWnd);

			if (ChildOn == TRUE) {
				StudentNumberList = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_CENTER | DT_VCENTER, 660, 418, 410, 35, hWnd, (HMENU)IDC_EDIT1, g_hInst, NULL);
				NameList = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_CENTER | DT_VCENTER, 1010, 662, 410, 35, hWnd, (HMENU)IDC_EDIT2, g_hInst, NULL);
				ChildOn = FALSE;
			}

			GetDlgItemText(hWnd, IDC_EDIT1, studentNumber, 100);
			GetDlgItemText(hWnd, IDC_EDIT2, name, 100);
			if (name[0] != '\0' && studentNumber[0] != '\0') {
				signIn(memdc);
				startButton = TRUE;
			}
			else
				startButton = FALSE;

			if (wcslen(studentNumber) == 10 && wcCheck == FALSE) {
				SetFocus(NameList);
				wcCheck = TRUE;
			}
			else if(wcslen(studentNumber) != 10 && wcCheck == TRUE)
				wcCheck = FALSE;
	
			

			DeleteObject(hFont);
			DeleteObject(hOldFont);
		}

		BitBlt(hdc, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom, memdc, 0, 0, SRCCOPY);

		DeleteObject(hBrush); 
		DeleteObject(oldBrush);
		DeleteObject(myPen);
		DeleteObject(oldPen);
		DeleteObject(hBitmap);
		DeleteObject(hbmMemOld);
		DeleteObject(hFont);
		DeleteObject(hOldFont);
		DeleteDC(memdc);
		DeleteDC(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}