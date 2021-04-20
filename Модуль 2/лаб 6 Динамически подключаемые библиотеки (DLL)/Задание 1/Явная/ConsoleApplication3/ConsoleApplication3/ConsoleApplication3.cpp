#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    HMODULE hMyDll;
        void (*Say)(char*);
        char* word;

        hMyDll = LoadLibrary(L"C:\\Users\\User\\source\\repos\\Dll1\\Debug\\Dll1.dll");
        if (hMyDll == NULL) { wcerr << L"error loading library" << endl; system("pause"); return 3; }

        word = (char*)GetProcAddress(hMyDll, "Message");
        if (!word) { wcerr << L"error loading message form library" << endl; system("pause"); return 4; }

        Say = (void(*)(char*))GetProcAddress(hMyDll, "SayMessage");
        if (!Say) { wcerr << L"error loading function from library" << endl; system("pause"); return 5; }

        Say(word);

        system("pause");
    FreeLibrary(hMyDll);
}