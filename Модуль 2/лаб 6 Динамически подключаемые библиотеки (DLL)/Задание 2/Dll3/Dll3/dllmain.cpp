// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <string>

using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) wchar_t Name[] = L"Calculator";

extern "C" __declspec(dllexport) wstring getDecNumber(wstring str) {
    int dec = 0;
    int x = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        int _int = str[i];
        if (_int == 48) dec += 0;
        else if (_int == 49) dec += (1 * (pow(2, x)));
        x++;
    }
    return to_wstring(dec);
    }

extern "C" __declspec(dllexport) wstring getBinNumber(int dec) {
    bool flag = false;
    if (dec < 0) {
        flag = true;
        dec = fabs(dec);
    }
    int bin = 0;
    for (int i = 0; dec > 0; i++) {
        bin += (dec % 2) * pow(10.0, i);
        dec /= 2;
    }
    if (flag) {
        bin = -bin;
    }
    return to_wstring(bin);
}