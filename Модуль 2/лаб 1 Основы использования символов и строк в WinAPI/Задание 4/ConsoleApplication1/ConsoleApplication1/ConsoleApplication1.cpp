#include <iostream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

int main()
{
    setlocale(0, "");
    wstring s;
    wcin >> s;
    const wchar_t* v = s.c_str();
    char *t=new char[wcslen(v)];
    if (WideCharToMultiByte(CP_ACP, 0, v, -1, t, wcslen(v)*4, 0, 0) == 0) {
        cout << GetLastError << endl;
        return -1;
    }
    else {
        cout << t << endl;
        return 0;
    }
}

