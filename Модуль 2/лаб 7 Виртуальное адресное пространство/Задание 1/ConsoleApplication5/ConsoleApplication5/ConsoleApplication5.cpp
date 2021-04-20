#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    setlocale(0, "");
    HANDLE hFile;
    char name[MAX_PATH] = "file.txt";

    hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cerr << "Ошибка открытия файла" << endl;
        cout << 1 << endl;
        system("pause");
        return 1;
    }

    HANDLE hFileMapping;
    hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

    if (!hFileMapping) {
        cerr << "Ошибка открытия файла" << endl;
        system("pause");
        return 1;
    }

    char* file;
    file = (char*)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);

    int count_a = 0;
    for (int i = 0; i < strlen(file); i++)
        if (file[i] == 'a') count_a++;

    cout << "В файле используется " << count_a << " букв \"a\"" << endl;
    UnmapViewOfFile((LPVOID)file);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
}

