// Ranking.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "Ranking.h"
#include <iostream>
#include <fstream>
#include <string>

#define Debug TRUE
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RANKING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RANKING));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RANKING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

typedef struct _Rank
{
	std::string name;
	int studentNum;
	int score;
}Rank;

typedef struct _node
{
	Rank data;
	_node* pNext = nullptr;
}Node;

CImage Rule;
CImage Effect;

Node* FirstComputerList = NULL;
Node* SecondComputerList = NULL;
Node* ThirdComputerList = NULL;
Node* TotalList = NULL;

int indexR;
int indexL;

int LdT = 0, LdL = 0;

void SetRanking()
{
	std::ifstream out;

	out.open("Rank\\1\\Ranking.txt");
	
	while (!out.eof())
	{
		Node* tmp = new Node;
		out >> tmp->data.name >> tmp->data.studentNum >> tmp->data.score;
		if (FirstComputerList == NULL)
			FirstComputerList = tmp;
		Node* i;
		for (i = FirstComputerList; i->pNext != nullptr; i = i->pNext)
		{}
		i->pNext = tmp;
	}

	out.close();

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		indexR = 0;
		indexL = 0;

		TCHAR LoadText2[1000];		
		TCHAR LoadText[1000];

		wsprintf(LoadText, "VFX\\RULE_00000.png");
		Rule.Load(LoadText);

		wsprintf(LoadText2, "VFX\\Re\\RANK_EFFECT_00000.png");
		Effect.Load(LoadText2);

		SetRanking();

		SetTimer(hWnd, 1, 34, NULL);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			RECT clientRECT;

			GetClientRect(hWnd, &clientRECT);

			if (Debug == FALSE)
			{
				if (indexR > 525)
					Effect.Draw(hdc, clientRECT);
				if (indexL == 0)
					Rule.Draw(hdc, clientRECT);
			}
			if (Debug == TRUE)
			{
				TextOut(hdc, 100, 100, FirstComputerList->data.name.c_str(), 6);
			}

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_TIMER:
	if (Debug == FALSE)
	{
		if (indexR < 539)
		{
			Rule.Destroy();
			TCHAR LoadText[1000];
			wsprintf(LoadText, "VFX\\RULE_%05d.png", indexR * 2);
			Rule.Load(LoadText);

			indexR++;
		}
		else if (indexL < 180)
		{
			if (indexL == 90 && LdT < 250)
			{
				LdT++;
				break;
			}
			indexL++;
			Effect.Destroy();
			TCHAR LoadText[1000];
			wsprintf(LoadText, "VFX\\Re\\RANK_EFFECT_%05d.png", indexL);
			Effect.Load(LoadText);
		}
		else
		{
			if (LdL < 250)
			{
				LdL++;
				break;
			}
			indexR = 0;
			indexL = 0;
			LdT = 0;
			LdL = 0;
		}
		InvalidateRect(hWnd, NULL, false);
	}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
