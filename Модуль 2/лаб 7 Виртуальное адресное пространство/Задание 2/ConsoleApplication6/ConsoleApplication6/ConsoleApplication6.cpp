#include <iostream>
#include <windows.h>

#define BLOCK_SIZE 32

using namespace std;

void print(string name, int file_size, char* content, int information = 0) {
    switch (information) {
        case 0:
            cout << "Входные данные" << endl;
            break;
        case 1:
            cout << "Выходные данные" << endl;
            break;
        default:
            break;
    }
    cout << "Имя файла:" << name << endl;
    cout << "Размер файла:" << file_size << endl;
    cout << "Содержимое файла:" << content << endl;
}

int main()
{
    setlocale(0, "");
    string name;
    int file_size;

    cout << "Введите название файла:" ;
    cin >> name;
    system("cls");

    HANDLE hFile;

    hFile = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cerr << "Ошибка открытия файла" << endl;
        system("pause");
        return 1;
    }

    HANDLE hFileMapping;
    hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (!hFileMapping) {
        cerr << "Ошибка открытия файла" << endl;
        system("pause");
        return 1;
    }

    char *content = (char*)MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

    file_size = strlen(content);

    print(name, file_size, content);

    if (file_size >= BLOCK_SIZE * 2) {

        HANDLE hHeap;
        hHeap = HeapCreate(0, 0, 0);
        if (hHeap == NULL) {
            cerr << "Ошибка создания кучи" << endl;
            system("pause");
            return 1;
        }

        char* tmp = (char*)HeapAlloc(hHeap, 0, BLOCK_SIZE);
        if (tmp == NULL) {
            cerr << "Ошибка не выделен блок памяти из кучи" << endl;
            system("pause");
            return 1;
        }

        for (int i = 0, j = 0; i < file_size / (BLOCK_SIZE * 2); i++, j+=2) {
            CopyMemory(tmp, &content[j * BLOCK_SIZE], BLOCK_SIZE);
            CopyMemory(&content[j * BLOCK_SIZE], &content[(j + 1) * BLOCK_SIZE], BLOCK_SIZE);
            CopyMemory(&content[(j + 1) * BLOCK_SIZE], tmp, BLOCK_SIZE);
        }

        if (HeapFree(hHeap, NULL, tmp) == 0) {
            cerr << "Ошибка блок памяти, выделенный из кучи не освобожден" << endl;
            system("pause");
            return 1;
        }

        if (HeapDestroy(hHeap) == 0) {
            cerr << "Ошибка куча не уничтожена" << endl;
            system("pause");
            return 1;
        }
    }

    cout << endl;
    print(name, file_size, content, 1);

    UnmapViewOfFile((LPVOID)content);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
}

