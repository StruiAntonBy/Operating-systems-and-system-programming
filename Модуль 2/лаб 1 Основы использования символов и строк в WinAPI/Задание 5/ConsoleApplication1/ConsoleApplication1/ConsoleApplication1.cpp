#include <iostream>
#include <Windows.h>

using namespace std;

wchar_t* Mystrrchr(wchar_t* str, wchar_t ch) {
    for (int i = wcslen(str); i>=0; i--) {
        if (str[i] == ch) {
            return &str[i];
        }
    }
    return NULL;
}

void main()
{
    setlocale(0, "");
    wchar_t s[] = L"Hello world!";
    wchar_t ch = 'l';
    wchar_t *MyP=Mystrrchr(s,ch);
    if (MyP) {
        wcout << L"Последнее вхождения символа " << ch << L" в строку \"" << s << L"\": " << (MyP - s) << endl;
    }
    else {
        wcout << L"Символ " << ch << L" не входит в строку \"" << s << L"\"" << endl;
    }
    wchar_t* p=wcsrchr(s, ch);
    if (p) {
        wcout << L"Последнее вхождения символа " << ch << L" в строку \""<< s << L"\": " << (p - s)<<endl;
    }
    else {
        wcout << L"Символ " << ch << L" не входит в строку \"" << s << L"\"" << endl;
    }
}
