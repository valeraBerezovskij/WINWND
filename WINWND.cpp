#include <windows.h>
#include <tchar.h>
#include"Resource.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");
HCURSOR hCursor1, hCursor2, hCursor3, hCursor4, hCursor5, hCursor6;
HICON hIcon;

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;


	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_CURSOR1));
	wcl.hbrBackground = (HBRUSH)GetStockObject(0);
	wcl.lpszMenuName = (LPCSTR)LoadMenu(hInst, "менюшка");
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassEx(&wcl))
		return 0;

	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("Каркас Windows приложения"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = GetModuleHandle(0);
	int x;
	int y;
	switch (uMessage)
	{
	case WM_CREATE:
	{
		hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
		hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
		hCursor3 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));
		hCursor4 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR4));
		hCursor5 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR5));
		hCursor6 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR6)); //def

		//hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	}
	break;
	case WM_MOUSEMOVE:
		RECT rect;
		GetClientRect(hWnd, &rect);
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (x <= rect.right * 0.25 && y <= rect.bottom * 0.25) {
			SetCursor(hCursor1);
		}
		else if (x >= rect.right * 0.75 && y <= rect.bottom * 0.25) {
			SetCursor(hCursor2);
		}
		else if ((x >= rect.right * 0.4 && x <= rect.right * 0.6) &&
				 (y >= rect.bottom * 0.4 && y <= rect.bottom * 0.6)) {
			SetCursor(hCursor3);
		}
		else if (x <= rect.right * 0.25 && y >= rect.bottom * 0.75) {
			SetCursor(hCursor4);
		}
		else if (x >= rect.right * 0.75 && y >= rect.bottom * 0.75) {
			SetCursor(hCursor5);
		}
		else {
			SetCursor(hCursor6);
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
