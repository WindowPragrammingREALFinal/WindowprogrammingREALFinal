// Ranking.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//
#include "stdafx.h"
#include "Ranking.h"
#include <iostream>
#include <fstream>
#include <string>
#include <atlbase.h>

#define Debug TRUE
#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RANKING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RANKING));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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

	//����
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

			hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����_Regular"));
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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


//�����ؼ� TotalRanking ����Ʈ�� �����
//����ϱ�