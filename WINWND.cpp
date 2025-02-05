#include "framework.h"
#include "WINWND.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  // Имя title bar
WCHAR szWindowClass[MAX_LOADSTRING];            // имя главного окна

// Описание прототипов функций:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//Главная main функция
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Инициализация глобальных строк   
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINWND, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Инициализация приложения
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINWND));

    MSG msg;

    //Запуск цикла обработки сообщений для окна
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

//  Регистрация класса окна
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //Создание объекта класса WNDCLASS(объект окна)
    WNDCLASSEXW wcex;

    //Заполнение структуры
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINWND));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINWND);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    //Регистрация окна в ОС
    return RegisterClassExW(&wcex);
}

//   Сохраняет дескриптор экземпляра и создает главное окно
//
//   В этой функции мы сохраняем дескриптор экземпляра в глобальной переменной,
//   создаем и отображаем главное окно программы
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохраняет дескриптор в глобальной переменной

   //Создание главного окна
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   //Проверка на корректность создания
   if (!hWnd)
   {
      return FALSE;
   }

   //Отображение окна
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//  Обработка сообщений главного окна.
//
//  WM_COMMAND  - обработка меню приложения
//  WM_PAINT    - рисует главное окно
//  WM_DESTROY  - закрытие окна
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            //Свитч событий окна
            switch (wmId)
            {
            //Нажатие about
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            //Закрытие окна
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    //Закрытие окна
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Функция хендлер для окна about
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE; // Обработчик инициализации диалогового окна

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam)); // Закрытие диалогового окна
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE; // выполняется если сообщение не обработано в свиче
}
