#include <iostream>
#include <Windows.h>

using namespace std;

int main(){
    setlocale(0, "");
    if (ShellExecute(NULL, NULL, L"file:///C:/Program%20Files/Microsoft%20Office/", NULL, NULL, SW_SHOW)<=(HINSTANCE)32) {
        cout <<GetLastError() <<endl;
    }
    return 0;
}