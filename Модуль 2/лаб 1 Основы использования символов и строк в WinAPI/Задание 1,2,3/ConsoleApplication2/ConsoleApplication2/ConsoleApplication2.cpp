#include <iostream>
#include <Windows.h>
#include <tchar.h>

#ifdef _UNICODE
	void _TPrintChar(wchar_t *v);
#else 
	void _TPrintChar(char *v);
#endif

using namespace std;

void _TPrintChar(char *v) {
	cout << v << endl;
}
void _TPrintChar(wchar_t* v) {
	wcout << v << endl;
}

void main()
{
	setlocale(0, "");
	TCHAR v[] = _T("Hello world!");
	TCHAR vr[] = _T("Привет, Мир!");
	_TPrintChar(v);
	_TPrintChar(vr);
}