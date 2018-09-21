// Ranking.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "Ranking.h"
#include <iostream>
#include <fstream>
#include <string>
#include <atlbase.h>

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

int TotalIndex = 0;
Rank TotalArray[18];

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
		{
			FirstComputerList = tmp;
			continue;
		}
		else if (FirstComputerList->pNext == NULL)
		{
			if (tmp->data.score > FirstComputerList->data.score)
			{
				FirstComputerList->pNext = tmp;
			}
			else
			{
				tmp->pNext = FirstComputerList;
				FirstComputerList = tmp;
			}
			continue;
		}
		if (tmp->data.score < FirstComputerList->data.score)
		{
			tmp->pNext = FirstComputerList;
			FirstComputerList = tmp;
			continue;
		}

		Node* i;
		bool br = false;
		for (i = FirstComputerList; i->pNext != nullptr; i = i->pNext)
		{
			if (tmp->data.score < i->data.score)
			{
				Node* saver = tmp->pNext;
				tmp->pNext = i;
				saver->pNext = tmp;
				br = true;
				break;
			}	
			tmp->pNext = i;
		}
		if (br == true)
			continue;
		if (tmp->data.score < i->data.score)
		{
			Node* saver = tmp->pNext;
			tmp->pNext = i;
			saver->pNext = tmp;
			continue;
		}
		i->pNext = tmp;
		tmp->pNext = NULL;
	}

	out.close();


	out.open("Rank\\2\\Ranking.txt");

	while (!out.eof())
	{
		Node* tmp = new Node;
		out >> tmp->data.name >> tmp->data.studentNum >> tmp->data.score;
		if (SecondComputerList == NULL)
		{
			SecondComputerList = tmp;
			continue;
		}
		else if (SecondComputerList->pNext == NULL)
		{
			if (tmp->data.score > SecondComputerList->data.score)
			{
				SecondComputerList->pNext = tmp;
			}
			else
			{
				tmp->pNext = SecondComputerList;
				SecondComputerList = tmp;
			}
			continue;
		}
		if (tmp->data.score < SecondComputerList->data.score)
		{
			tmp->pNext = SecondComputerList;
			SecondComputerList = tmp;
			continue;
		}
		Node* i;
		bool br = false;
		for (i = SecondComputerList; i->pNext != nullptr; i = i->pNext)
		{
			if (tmp->data.score < i->data.score)
			{
				Node* saver = tmp->pNext;
				tmp->pNext = i;
				saver->pNext = tmp;
				br = true;
				break;
			}
			tmp->pNext = i;
		}
		if (br == true)
			continue;
		if (tmp->data.score < i->data.score)
		{
			Node* saver = tmp->pNext;
			tmp->pNext = i;
			saver->pNext = tmp;
			continue;
		}
		i->pNext = tmp;
		tmp->pNext = NULL;
	}

	out.close();

	out.open("Rank\\3\\Ranking.txt");

	while (!out.eof())
	{
		Node* tmp = new Node;
		out >> tmp->data.name >> tmp->data.studentNum >> tmp->data.score;
		if (ThirdComputerList == NULL)
		{
			ThirdComputerList = tmp;
			continue;
		}
		else if (ThirdComputerList->pNext == NULL)
		{
			if (tmp->data.score > ThirdComputerList->data.score)
			{
				ThirdComputerList->pNext = tmp;
			}
			else
			{
				tmp->pNext = ThirdComputerList;
				ThirdComputerList = tmp;
			}
			continue;
		}
		if (tmp->data.score < ThirdComputerList->data.score)
		{
			tmp->pNext = ThirdComputerList;
			ThirdComputerList = tmp;
			continue;
		}
		Node* i;
		bool br = false;
		for (i = ThirdComputerList; i->pNext != nullptr; i = i->pNext)
		{
			if (tmp->data.score < i->data.score)
			{
				Node* saver = tmp->pNext;
				tmp->pNext = i;
				saver->pNext = tmp;
				br = true;
				break;
			}
			tmp->pNext = i;
		}
		if (br == true)
			continue;
		if (tmp->data.score < i->data.score)
		{
			Node* saver = tmp->pNext;
			tmp->pNext = i;
			saver->pNext = tmp;
			continue;
		}
		i->pNext = tmp;
		tmp->pNext = NULL;
	}

	out.close();

	//머지
	while(TotalIndex < 18)
	{
		Node* Ftmp; Node* Stmp; Node* Ttmp;
		Node* Fztmp; Node* Sztmp; Node* Tztmp;
		Ftmp = FirstComputerList;
		Stmp = SecondComputerList;
		Ttmp = ThirdComputerList;
		Fztmp = Ftmp;
		Sztmp = Stmp;
		Tztmp = Ttmp;		

		for (Ftmp = FirstComputerList; Ftmp->pNext != nullptr; Ftmp = Ftmp->pNext)
			Fztmp = Ftmp;
		for (Stmp = SecondComputerList; Stmp->pNext != nullptr; Stmp = Stmp->pNext)
			Sztmp = Stmp;
		for (Ttmp = ThirdComputerList; Ttmp->pNext != nullptr; Ttmp = Ttmp->pNext)
			Tztmp = Ttmp;

		if (Fztmp == NULL && Sztmp == NULL && Tztmp == NULL)
			break;

		int d;
		if (Ftmp->data.score > Stmp->data.score)
		{
			if (Ftmp->data.score > Ttmp->data.score)
			{
				d = 1;
			}
			else
			{
				d = 3;
			}
		}
		else
		{
			if (Stmp->data.score > Ttmp->data.score)
			{
				d = 2;
			}
			else
			{
				d = 3;
			}
		}
		switch (d)
		{
		case 1:
			memcpy(&TotalArray[TotalIndex], &Ftmp->data, sizeof(Rank));
			TotalIndex++;
			//delete Ftmp;
			Fztmp->pNext = NULL;
			break;
		case 2:
			memcpy(&TotalArray[TotalIndex], &Stmp->data, sizeof(Rank));
			TotalIndex++;
			//delete Stmp;
			Sztmp->pNext = NULL;
			break;
		case 3:
			memcpy(&TotalArray[TotalIndex], &Ttmp->data, sizeof(Rank));
			TotalIndex++;
			//delete Ttmp;
			Tztmp->pNext = NULL;
			break;
		}
	}
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

		wsprintf(LoadText, L"VFX\\RULE_00000.png");
		Rule.Load(LoadText);

		wsprintf(LoadText2, L"VFX\\Re\\RANK_EFFECT_00000.png");
		Effect.Load(LoadText2);

		SetRanking();

		SetTimer(hWnd, 1, 34, NULL);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			RECT clientRECT;

			HFONT hFont, saveFont;

			hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("다음_Regular"));
			SetTextColor(hdc,RGB(62, 151, 255));
			saveFont = (HFONT)SelectObject(hdc, hFont);

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
				USES_CONVERSION;

				Node* i;
				int a = 0;
				
				/*for (i = SecondComputerList; i != nullptr; i = i->pNext)
				{
					WCHAR LoadText[20];
					WCHAR LoadTextx[20];

					TextOut(hdc, 100, 100 + 50*a, A2W(i->data.name.c_str()), 3);
					wsprintf(LoadText, L"%d", i->data.studentNum);
					TextOut(hdc, 280, 100 + 50 * a, LoadText, 20);
					wsprintf(LoadTextx, L"%d", i->data.score);
					TextOut(hdc, 700, 100 + 50 * a, LoadTextx, 20);
					a++;
				}*/
				for (int i = 0; i < 18; i++)
				{
					WCHAR LoadText[20];
					WCHAR LoadTextx[20];

					TextOut(hdc, 100, 100 + 50 * i, A2W(TotalArray[i].name.c_str()), 3);
					wsprintf(LoadText, L"%d", TotalArray[i].studentNum);
					TextOut(hdc, 280, 100 + 50 * i, LoadText, 20);
					wsprintf(LoadTextx, L"%d", TotalArray[i].score);
					TextOut(hdc, 700, 100 + 50 * i, LoadTextx, 20);
				}
			}

			
			DeleteObject(SelectObject(hdc, saveFont));
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
			wsprintf(LoadText, L"VFX\\RULE_%05d.png", indexR * 2);
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
			wsprintf(LoadText, L"VFX\\Re\\RANK_EFFECT_%05d.png", indexL);
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


//정렬해서 TotalRanking 리스트로 만들기
//출력하기