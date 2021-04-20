#include <iostream>
#include <Windows.h>

using namespace std;

int main(){
    setlocale(0, "");
    STARTUPINFO cif;
    ZeroMemory(&cif, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;
    if (!CreateProcess(L"C:\\Program Files\\Microsoft Office\\Office16\\EXCEL.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi)) {
        cout << GetLastError() << endl;
        return -1;
    }

    cout<<"PID:"<< GetProcessId(pi.hProcess)<<endl;
    cout<<"HANDLE:"<< pi.hProcess <<endl;

    return 0;
}

