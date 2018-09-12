#pragma once
#include <Windows.h>
#include <atlImage.h>

void Health(HDC memdc, int Life, int count);

//void Result(HDC memdc, int score, int slide, HWND hWnd);

BOOL screenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight, HWND hWnd);

BOOL openScreenAnimation(HDC memdc, int left, int right, int top, int bottom, int totalRight, int clientRight);

void remain(HDC memdc, int correct, HWND hWnd, COLORREF rgb, int slide, int slideX);

void Start(HDC memdc, int moveX, HWND hWnd);

void bottomBarLoad();
void bottomBar(HDC memdc, COLORREF rgb, HWND hWnd);
void bottomBarDestroy();

void scoreImage(HDC memdc, HWND hWnd, int Totalscore, int count);

void BGLoad();
void BGDraw(HDC memdc, HWND hWnd);
void BGDestroy();

void login(HDC memdc, HWND hWnd);

void signIn(HDC memdc);

void LoadBack();
void DeleteBack();

void resetTemp();

void TempLoad();
void TempDraw(HDC memdc, int moveY, HWND hWnd);
void TempDestroy();