#include <Windows.h>
#include <atlimage.h>
#include <iostream>
#include <fstream>

#define Height 1250
#define Weight 700

HPEN MyPen, OldPen;
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Make No Difference!";

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
	hWnd = CreateWindow(lpszClass, L"Settings", NULL, 100, 50, Height, Weight, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

CImage img;
CImage imgg;
CImage r;
CImage e;
CImage C_Check[2];
std::ofstream dir;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	HDC memDC;
	HBITMAP hBitmap;
	HBRUSH hBrush, oldBrush;

	static WCHAR LoadText[512] = { 0 };

	static BOOL edit = FALSE, imageOn = FALSE;
	static BOOL keyDown = FALSE;
	static int mx = 0, my = 0;
	static BOOL MouseOn[6] = {0};

	static BOOL exhibit = FALSE;

	static POINT p[5][2] = { 0 };
	static int pCount = 0;
	switch (iMessage) { 
	case WM_CREATE:
		DragAcceptFiles(hWnd, TRUE);
		r.Load(L"r.jpg");
		e.Load(L"e.png");
		C_Check[0].Load(L"C_Check.png");
		C_Check[1].Load(L"C_Check2.png");
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, 1250, 750);
		SelectObject(memDC, hBitmap);

		hBrush = CreateSolidBrush(RGB(111, 174, 186));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);
		Rectangle(memDC, -10, -10, 1250, 700);
		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(145, 145, 145));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);
		Rectangle(memDC, 10, 10, 610, 610);
		Rectangle(memDC, 620, 10, 1230, 610);
		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(255, MouseOn[5] * 53, MouseOn[5] * 53));
		oldBrush = (HBRUSH)SelectObject(memDC, hBrush);
		RoundRect(memDC, 1137, 615, 1230, 660, 20, 20);
		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);

		for (int i = 0; i < pCount; i++)
		{
			if (imageOn)
				C_Check[0].Draw(memDC, 630 + i * 40, 612);
		}
		for (int i = pCount; i < 5; i++)
		{
			if (imageOn)
				C_Check[1].Draw(memDC, 630 + i * 40, 612);
		}

		if (!img.IsNull())
		{
			img.Draw(memDC, 10, 10, 600, 600);
			if (!imgg.IsNull())
			{
				imgg.Draw(memDC, 620, 10, 610, 600);
				imageOn = TRUE;
			}

		}

		SetBkMode(memDC, TRANSPARENT);

		TextOut(memDC, 1180, 630, L"X", lstrlen(L"X"));

		for (int i = 0; i < 4; i++)
		{
			hBrush = CreateSolidBrush(RGB(190 + MouseOn[i]*28, 213 - MouseOn[i]*103, 218 - MouseOn[i] * 106));
			oldBrush = (HBRUSH)SelectObject(memDC, hBrush);
			RoundRect(memDC, 10 + 10 * i + i * 113, 615, 110 + 10 * i + 113 * i, 660,20,20);
			SelectObject(memDC, oldBrush);
			DeleteObject(hBrush);
		}

		{
			WCHAR mXY[40];
			wsprintf(mXY, L"( %d , %d )", mx, my);
			TextOut(memDC, mx + 10, my + 10, mXY, lstrlen(mXY));
		}
		
		if (edit)
		{
			SetTextColor(memDC, RGB(0, 0, 0));
			TextOut(memDC, 26, 630, L"입력 종료", lstrlen(L"입력 종료"));
			TextOut(memDC, 22 + 1 * 130, 630, L"되돌리기", lstrlen(L"되돌리기"));
			SetTextColor(memDC, RGB(100, 100, 100));
		}
		else
		{
			SetTextColor(memDC, RGB(100, 100, 100));
			TextOut(memDC, 22 + 1 * 130, 630, L"되돌리기", lstrlen(L"되돌리기"));
			SetTextColor(memDC, RGB(0, 0, 0));
			if (!imageOn)
				SetTextColor(memDC, RGB(100, 100, 100));
			TextOut(memDC, 26, 630, L"좌표 입력", lstrlen(L"좌표 입력"));
		}
		
		TextOut(memDC, 20 + 2 * 130, 630, L"초기화", lstrlen(L"초기화"));
		TextOut(memDC, 6 + 3 * 130, 630, L"좌표 저장", lstrlen(L"좌표 저장"));

		if (edit && keyDown)
		{
			BLENDFUNCTION bf;
			bf.AlphaFormat = 0;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = 30;
			r.AlphaBlend(memDC, p[pCount][0].x, p[pCount][0].y, p[pCount][1].x - p[pCount][0].x, p[pCount][1].y - p[pCount][0].y, 0, 0, r.GetWidth(), r.GetHeight(), 125, AC_SRC_OVER);
		}
		for (int i = 0; i<pCount; i++)
			r.AlphaBlend(memDC, p[i][0].x, p[i][0].y, p[i][1].x - p[i][0].x, p[i][1].y - p[i][0].y, 0, 0, r.GetWidth(), r.GetHeight(), 125, AC_SRC_OVER);


		if (exhibit)
			e.Draw(memDC, 565, 615, 45, 45);
		/*{
			WCHAR tmp[100];
			wsprintf(tmp, L"%d %d %d %d %d", p[0][0].x, p[0][0].y, p[0][1].x, p[0][1].y, pCount);
			TextOut(memDC, 500, 500, tmp, lstrlen(tmp));
		}*/
		BitBlt(hDC, 0, 0, 1250, 750, memDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		SelectObject(memDC, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(hBitmap);
		DeleteDC(memDC);
		break;
	case WM_DROPFILES:
	{
		
		HDROP hDrop = (HDROP)wParam;
		DragQueryFile((HDROP)wParam, 0, LoadText, sizeof(wchar_t) * 512);

		img.Load(LoadText);

		{
			int findNULL;
			for (int i = 0; i < 512; i++)
			{
				if (LoadText[i] == '\0')
				{
					findNULL = i;
					break;
				}
			}
			LoadText[findNULL - 5] = '1';
		}
		imgg.Load(LoadText);
		DragFinish(hDrop);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (mx > 10 && mx < 610 && my > 10 && my < 610)
			keyDown = TRUE;

		if (edit && pCount < 5)
		{
			p[pCount][0].x = mx;
			p[pCount][0].y = my;
			p[pCount][1].x = mx;
			p[pCount][1].y = my;
		}
		for (int i = 0; i < 6; i++)
		{
			if (MouseOn[i] == TRUE)
			{
				switch (i)
				{
				case 0:
					if (imageOn)
					{
						if (edit)
							edit = FALSE;
						else
						{
							edit = TRUE;
							//if (pCount == 0)
							//pCount--;
						}
					}
					break;
				case 1:
					if (imageOn && edit)
					{
						if (pCount > 0)
						{
							pCount--;
							p[pCount][0].x = 0;
							p[pCount][0].y = 0;
							p[pCount][1].x = 0;
							p[pCount][1].y = 0;
						}
					}
					break;
				case 2:
					if (imageOn && !edit)
					{
						pCount = 0;
						for (int i = 0; i < 5; i++)
						{
							p[i][0].x = 0;
							p[i][0].y = 0;
							p[i][1].x = 0;
							p[i][1].y = 0;
						}
					}
					break;
				case 3:
					if (imageOn && !edit && !exhibit)
					{
						{
							int findNULL;
							for (int i = 0; i < 512; i++)
							{
								if (LoadText[i] == '\0')
								{
									findNULL = i;
									break;
								}
							}
							LoadText[findNULL - 3] = 't';
							LoadText[findNULL - 2] = 'x';
							LoadText[findNULL - 1] = 't';

							dir.open(LoadText,std::ios_base::out);
							dir << pCount << " ";
							for (int i = 0; i < pCount; i++)
								dir << p[i][0].x -10 << " " << p[i][0].y -10 << " " << p[i][1].x - 10 << " " << p[i][1].y - 10 << " ";
							dir.close();
							MessageBox(hWnd, L"좌표를 성공적으로 저장했습니다.", L"save", NULL);
						}

					}
					if (exhibit)
					{
						MessageBox(hWnd, L"좌표 저장에 실패했습니다.", L"error", NULL);
					}
					break;
				case 4:
					if (imageOn && !edit)
					{
						//NULL
					}
					break;
				case 5:
					PostQuitMessage(0);
					break;
				}
			}
		}
		break;

	case WM_LBUTTONUP:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		keyDown = FALSE;

		if (edit && pCount < 5)
		{
			p[pCount][1].x = mx;
			p[pCount][1].y = my;
			if (p[pCount][1].x > 610)
				p[pCount][1].x = 610;
			if (p[pCount][1].x < 10)
				p[pCount][1].x = 10;
			if (p[pCount][1].y > 610)
				p[pCount][1].y = 610;
			if (p[pCount][1].y < 10)
				p[pCount][1].y = 10;

			if (p[pCount][0].x > p[pCount][1].x || p[pCount][0].y > p[pCount][1].y)
			{

			}
			else if (pCount < 5 && p[pCount][1].x > 10 && p[pCount][1].x < 610 && p[pCount][1].y > 10 && p[pCount][1].y < 610)
				pCount++;
		}
		{
			BOOL chk = FALSE;
			for (int i = 0; i < pCount; i++)
			{
				for (int j = 0; j < i; j++)
				{
					RECT tmp1, tmp2;
					RECT check;

					tmp1.left = p[j][0].x;
					tmp1.top = p[j][0].y;
					tmp1.right = p[j][1].x;
					tmp1.bottom = p[j][1].y;

					tmp2.left = p[i][0].x;
					tmp2.top = p[i][0].y;
					tmp2.right = p[i][1].x;
					tmp2.bottom = p[i][1].y;

					if (IntersectRect(&check, &tmp1, &tmp2))
					{
						chk = TRUE;
					}
				}
			}
			if (chk)
				exhibit = TRUE;
			else
				exhibit = FALSE;
		}
		
		break;

	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		if (edit && keyDown && pCount < 5)
		{
			p[pCount][1].x = mx;
			p[pCount][1].y = my;
			if (p[pCount][1].x > 610)
				p[pCount][1].x = 610;
			if (p[pCount][1].x < 10)
				p[pCount][1].x = 10;
			if (p[pCount][1].y > 610)
				p[pCount][1].y = 610;
			if (p[pCount][1].y < 10)
				p[pCount][1].y = 10;
		}
		if (my > 615 && my < 660)
		{
			for (int i = 0; i < 5; i++)
			{
				if (mx > 10 + 10 * i + i * 113 && mx < 110 + 10 * i + 113 * i)
				{
					MouseOn[i] = TRUE;
					InvalidateRect(hWnd, NULL, false);
				}
				else
					MouseOn[i] = FALSE;
				if (mx > 1137 && mx < 1230)
				{
					MouseOn[5] = TRUE;
					InvalidateRect(hWnd, NULL, false);
				}
				else
					MouseOn[5] = FALSE;
			}
		}
		else
		{
			for (int i = 0; i < 6; i++)
				MouseOn[i] = FALSE;
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}