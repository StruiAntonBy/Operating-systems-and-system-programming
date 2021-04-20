#include <iostream>
#include <Windows.h>

using namespace std;

DWORD WINAPI thread2(LPVOID t) {
    for (;;) {
        Beep(294, 1000 / 8);
        Beep(440, 1000 / 4);
        Beep(262 * 2, 1000 / 4);
        Beep(330 * 2, 1000 / 4);
        Beep(415, 1000 / 8);
    }
}

int main(){
    setlocale(0, "");
    HANDLE hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
    for (;;) {
        int a;
        cout<<"1.Приостановить"<<endl;
        cout<<"2.Выход"<<endl;
        cin >> a;
        switch (a) {
            case 1:
                system("cls");
                if (SuspendThread(hThread2)==-1) {
                    system("cls");
                    cout << GetLastError() << endl;
                    return 2;
                }
                int b;
                cout << "1.Возобновить" << endl;
                cout << "2.Выход" << endl;
                cin >> b;
                switch (b) {
                    case 1:
                        system("cls");
                        if (ResumeThread(hThread2)==-1) {
                            system("cls");
                            cout << GetLastError() << endl;
                            return 3;
                        }
                        break;
                    case 2:
                        if (TerminateThread(hThread2, 0)==0) {
                            system("cls");
                            cout << GetLastError() << endl;
                            return 1;
                        }
                        return 0;
                    default:
                        system("cls");
                        break;
                }
                break;
            case 2:
                if (TerminateThread(hThread2, 0)==0) {
                    system("cls");
                    cout<<GetLastError()<<endl;
                    return 1;
                }
                return 0;
            default:
                system("cls");
                break;
        }
    }
}

