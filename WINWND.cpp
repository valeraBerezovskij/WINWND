// ���� WINDOWS.H �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows. 
#include <windows.h>
#include <tchar.h>


// �������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������");	/* ��� ������ ���� */

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;


	// 1. ����������� ������ ����
	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX
	// ������������ �� ����, ���� ������� ������ �� ����������� ��� �� ���������
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - ����� ������ ����
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ �������	
	wcl.hbrBackground = (HBRUSH)GetStockObject(0);	// ���������� ���� ����� ������
	wcl.lpszMenuName = (LPCSTR)LoadMenu(hInst, "�������");	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

	// 2. ����������� ������ ����
	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	// 3. �������� ����
	// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	//��� ������ ����
		TEXT("������ Windows ����������"), // ��������� ����
		WS_OVERLAPPEDWINDOW,				// ����� ����
		/* ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����  */
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������

	// 4. ����������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // ����������� ����

	// 5. ������ ����� ��������� ���������
	while (GetMessage(&Msg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ���������
	{
		TranslateMessage(&Msg);	// ���������� ���������
		DispatchMessage(&Msg);	// ��������������� ���������
	}
	return Msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	int res;

	TCHAR szWndStr1[32] = TEXT("Super text.");
	TCHAR szWndStr2[32] = TEXT("I love bees");
	TCHAR szWndStr3[32] = TEXT("TEXT TEXT TEXT!!");

	TCHAR szFinalMsg[32] = TEXT("Number of chars: ");
	TCHAR szBuff[32];
	const int nNumberWnds = 3;

	int nNumber = (lstrlen(szWndStr1) + lstrlen(szWndStr2) + lstrlen(szWndStr2)) / nNumberWnds;
	_itoa_s(nNumber, szBuff, 10);

	switch (uMessage)
	{
	case WM_SHOWWINDOW:
		res = MessageBox(hWnd, szWndStr1, TEXT("window title"), MB_OK | MB_ICONINFORMATION);
		if (res == IDOK) {
			res = MessageBox(hWnd, szWndStr2, TEXT("AXAXXAXAX"), MB_OK | MB_ICONINFORMATION);
		}
		if (res == IDOK) {
			res = MessageBox(hWnd, szWndStr3, TEXT("RESPECT"), MB_OK | MB_ICONINFORMATION);
		}
		MessageBox(hWnd, lstrcat(szFinalMsg, szBuff), TEXT("RESPECT"), MB_OK | MB_ICONINFORMATION);

		break;
	case WM_DESTROY: // ��������� � ���������� ���������/*
		//MessageBox(0, TEXT("HELLO WORLD"), TEXT("���� ���������"), MB_OK | MB_ABORTRETRYIGNORE);
		PostQuitMessage(0); // ������� ��������� WM_QUIT

		break;
	default:
		// ��� ���������, ������� �� �������������� � ������ ������� ������� 
		// ������������ ������� Windows �� ��������� �� ���������

		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
