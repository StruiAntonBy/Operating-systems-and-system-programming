#include "framework.h"
#include "WindowsProject12.h"

#define idBtn 1001
#define idBtnExcel 1002
#define idBtnWord 1003
#define idBtnPowerPoint 1004

void MenuBtnClick(HWND hWnd) {
    DestroyWindow(GetDlgItem(hWnd, idBtn));
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"C:\\excel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    HWND hButtonExcel = CreateWindow(L"BUTTON", L"excel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 0, 0, 50, 50, hWnd, (HMENU)idBtnExcel, GetModuleHandle(NULL), NULL);
    SendMessage(hButtonExcel, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    hBitmap = (HBITMAP)LoadImage(NULL, L"C:\\word.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    HWND hButtonWord = CreateWindow(L"BUTTON", L"word", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 70, 0, 50, 50, hWnd, (HMENU)idBtnWord, GetModuleHandle(NULL), NULL);
    SendMessage(hButtonWord, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    hBitmap = (HBITMAP)LoadImage(NULL, L"C:\\PowerPoint.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    HWND hButtonPowerPoint = CreateWindow(L"BUTTON", L"PowerPoint", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP, 140, 0, 50, 50, hWnd, (HMENU)idBtnPowerPoint, GetModuleHandle(NULL), NULL);
    SendMessage(hButtonPowerPoint, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
}

void BtnClick(HWND hWnd, wchar_t *str) {
    STARTUPINFO cif;
    ZeroMemory(&cif, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;
    if (!CreateProcess(str, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi)) {
        MessageBox(NULL,L"Check if the program is installed",L"Error", MB_OK);
    }
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode){
    WNDCLASS wcl;
    wcl.hInstance = hThisInst;
    wcl.lpszClassName = L"MainWindowClass";
    wcl.lpfnWndProc = MainWindowProc;
    wcl.style = 0;
    wcl.lpszMenuName = NULL;
    wcl.hIcon = LoadIcon(hThisInst, MAKEINTRESOURCE(IDI_ICON1));
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;

    if (!RegisterClass(&wcl)) return 0;

    HWND hWnd;
    hWnd = CreateWindow(L"MainWindowClass", NULL, WS_POPUP, 0, 812, 1920, 50, HWND_DESKTOP, NULL, hThisInst, NULL);

    CreateWindow(L"BUTTON", L"Menu", WS_CHILD | WS_BORDER | WS_VISIBLE, 0, 0, 50, 50, hWnd, (HMENU)idBtn, hThisInst, NULL);

    ShowWindow(hWnd, nWinMode);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            switch (LOWORD(wParam)) {
                case idBtn:
                    MenuBtnClick(hWnd);
                    break;
                case idBtnExcel:
                    BtnClick(hWnd, (wchar_t*)L"C:\\Program Files\\Microsoft Office\\Office16\\EXCEL.exe");
                    break;
                case idBtnWord:
                    BtnClick(hWnd, (wchar_t*)L"C:\\Program Files\\Microsoft Office\\Office16\\WINWORD.exe");
                    break;
                case idBtnPowerPoint:
                    BtnClick(hWnd, (wchar_t*)L"C:\\Program Files\\Microsoft Office\\Office16\\POWERPNT.exe");
                    break;
            }
        }
        break;
    case WM_KEYDOWN:
        switch (wParam) {
            case VK_ESCAPE:
                SendMessage(hWnd, WM_DESTROY, 0, 0);
                break;
            default:
                break;
        }
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
