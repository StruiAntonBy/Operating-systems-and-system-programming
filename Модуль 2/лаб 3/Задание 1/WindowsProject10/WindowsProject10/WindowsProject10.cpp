// WindowsProject10.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "WindowsProject10.h"
#include "PlateWindow.h"

// прототип оконной функции
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
    // Описание класса главного окна приложения
    WNDCLASS wcl;
    wcl.hInstance = hThisInst;
    wcl.lpszClassName = L"MainWindowClass";
    wcl.lpfnWndProc = MainWindowProc;
    wcl.style = 0;
    wcl.lpszMenuName = NULL;
    wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    // Регистрация класса главного окна приложения
    if (!RegisterClass(&wcl)) return 0;

    // Создание главного окна приложения
    HWND hWnd;
    hWnd = CreateWindow(L"MainWindowClass", L"Пример обработки сообщений",
        WS_OVERLAPPEDWINDOW, 0, 0, 300, 300, HWND_DESKTOP, NULL, hThisInst, NULL);
    ShowWindow(hWnd, nWinMode);
    UpdateWindow(hWnd);

    // Регистрация класса внутреннего окна
    RegisterPlateWindow();
    // Создание внутреннего окна
    CreateWindow(L"PlateWindowClass", L"Пластина", WS_CHILD | WS_VISIBLE,
        20, 20, 200, 200, hWnd, NULL, hThisInst, NULL);

    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Оконная функция главного окна приложения
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
