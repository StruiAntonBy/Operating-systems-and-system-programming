#include <iostream>
#include <windows.h>

using namespace std;

extern "C" __declspec(dllimport) char Message[];
extern "C" __declspec(dllimport) void SayMessage(char* message);

int main()
{
    char* message = Message;
    SayMessage(message);
    system("pause");
}