#include <iostream>
#include <windows.h>

using namespace std;

int main(){
    setlocale(0, "");

    STARTUPINFO cif;
    ZeroMemory(&cif, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;
    wchar_t str[] = L"C:\\Program Files\\WinRAR\\WinRAR.exe C:\\Archive.zip";
    if (!CreateProcess(NULL,str,NULL,NULL,FALSE,NULL,NULL,NULL, &cif, &pi)) {
        cout<<GetLastError()<<endl;
        return -1;
    }

    return 0;
}
