#include "framework.h"
#include "WindowsProject8.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>

using namespace std;

#define idEd 1001
#define idBtn0 1002
#define idBtn1 1003
#define idBtn2 1004
#define idBtn3 1005
#define idBtn4 1006
#define idBtn5 1007
#define idBtn6 1008
#define idBtn7 1009
#define idBtn8 1010
#define idBtn9 1011
#define idBtn10 1012
#define idBtn11 1013
#define idBtn12 1014

int Expression(wstring expression);               //разбивает выражение на слагаемые и суммирует их
int Term(wstring& expression, int& index);        //возвращает значение первого слагаемого начиная с позиции index выполняя бинарные операции
int Number(wstring& expression, int& index);      //извлекает первое число начиная с позиции index выполняя унарные операции
wstring Extract(wstring& expression, int& index);     //извлекает выражение из скобок

int Expression(wstring expression) {
    if (expression.length() == 0)
        return 0;
    int value;
    int index = 0;                          //текущая позиция курсора, передается по ССЫЛКЕ
    value = Term(expression, index);        //извлекаем первое слагаемое
    while (index < expression.length()) {
        //разбиваем строку на слагаемые и суммируем/вычитаем их
        switch (expression[index++]) {
        case L'+':
            value = value + Term(expression, index);
            break;
        case L'-':
            value = value - Term(expression, index);
            break;
        }
    }
    return value;
}

int Term(wstring& expression, int& index) {
    int value;                           //значение текущего слагаемого
    value = Number(expression, index);      //извлечение первого числа
    //бинарные операции
    while (true) {
        if (expression[index] == L'*') {
            index++;
            value = value * Number(expression, index);
            continue;
        }
        if (expression[index] == L'/') {
            index++;
            int res = Number(expression, index);
            if (res == 0) {
                MessageBox(NULL, L"Division by zero", L"Message", MB_OK);
                break;
            }
            value = value / res;
            continue;
        }
        else
            break;
    }
    return value;
}

int Number(wstring& expression, int& index) {
    int value = 0;           //число    
    //скобки
    if (expression[index] == L'(') {
        value = Expression(Extract(expression, index));
        return value;
    }
    //если число
    while (isdigit(expression[index])) {
        value = 10 * value + (expression[index] - L'0');
        index++;
    }
    //если не вещественное
    if (expression[index] != '.')
        return value;
}

wstring Extract(wstring& expression, int& index) {
    index++;                    //пропускаем первую левую скобку
    int Lbrackets = 1;          //счетчик левых скобок
    wstring substring;
    while (index < expression.length()) {
        if ((expression[index] == L')') && (Lbrackets == 1)) {
            index++;
            return substring;
        }
        if (expression[index] == L'(')
            Lbrackets++;
        if (expression[index] == L')')
            Lbrackets--;
        substring.push_back(expression[index++]);
    }
    return substring;
}

class Translator {
public:
    wstring getDecNumber(wstring str) {
        int dec = 0;
        int x = 0;
        for (int i = str.length() - 1; i >= 0; i--) {
            int _int = str[i];
            if (_int == 48) dec += 0;
            else if (_int == 49) dec += (1 * (pow(2, x)));
            x++;
        }
        return to_wstring(dec);
    }
    wstring getBinNumber(int dec) {
        bool flag = false;
        if (dec < 0) {
            flag = true;
            dec = fabs(dec);
        }
        int bin = 0;
        for (int i = 0; dec > 0; i++) {
            bin += (dec % 2) * pow(10.0, i);
            dec /= 2;
        }
        if (flag) {
            bin = -bin;
        }
        return to_wstring(bin);
    }
};

wstring GetResult(wstring str) {
    int k1 = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == L'0' || str[i] == L'1') {
            k1 = i;
            int k2 = str.length();
            for (int j = i; j < str.length(); j++) {
                if (str[j] != L'0' && str[j] != L'1') {
                    k2 = j;
                    break;
                }
            }
            wstring sub = str.substr(k1, k2 - k1);
            Translator tr;
            wstring dec = tr.getDecNumber(sub);
            str.replace(k1, sub.length(), dec);
            i = k1 + dec.length();
        }
        if (str[i] == L'÷') {
            str[i] = L'/';
        }
    }
    return str;
}

void BtnClickNum(HWND hWnd,wchar_t ch){
    HWND hEdit = GetDlgItem(hWnd, idEd);
    int n = GetWindowTextLengthW(hEdit);
    wchar_t* buf = new wchar_t[n+2];
    GetWindowTextW(hEdit,buf,n+1);
    buf[n] = ch;
    buf[n + 1] = L'\0';
    SetWindowTextW(hEdit, buf);
    delete[] buf;
}

void BtnClickEqually(HWND hWnd) {
    HWND hEdit = GetDlgItem(hWnd, idEd);
    int n = GetWindowTextLengthW(hEdit);
    if (n == 0) {
        return;
    }
    wchar_t* buf = new wchar_t[n+1];
    GetWindowTextW(hEdit, buf, n+1);
    if (buf[n - 1] == L'-' || buf[n - 1] == L'+' || buf[n - 1] == L'*' || buf[n - 1] == L'÷') {
        delete[] buf;
        return;
    }
    Translator tr;
    SetWindowTextW(hEdit, tr.getBinNumber(Expression(GetResult(wstring(buf)))).c_str());
    delete[] buf;
}

void BtnClickClean(HWND hWnd) {
    HWND hEdit = GetDlgItem(hWnd, idEd);
    SetWindowTextW(hEdit, NULL);
}

void BtnClickBackspace(HWND hWnd) {
    HWND hEdit = GetDlgItem(hWnd, idEd);
    int n = GetWindowTextLengthW(hEdit);
    if (n == 0) {
        return;
    }
    wchar_t* buf = new wchar_t[n];
    GetWindowTextW(hEdit, buf, n);
    buf[n-1] = L'\0';
    SetWindowTextW(hEdit, buf);
    delete[] buf;
}

void BtnClickOper(HWND hWnd, wchar_t ch) {
    HWND hEdit = GetDlgItem(hWnd, idEd);
    int n = GetWindowTextLengthW(hEdit);
    wchar_t* buf = new wchar_t[n + 2];
    GetWindowTextW(hEdit, buf, n + 1);
    if (n == 0) {
        if (ch == L'-' || ch == L'+'){
            buf[n] = ch;
            buf[n + 1] = L'\0';
            SetWindowTextW(hEdit, buf);
            delete[] buf;
            return;
        }
        else {
            delete[] buf;
            return;
        }
    }
    else if (buf[n-1] == L'-' || buf[n-1] == L'+' || buf[n-1] == L'*' || buf[n-1] == L'÷') {
        delete[] buf;
        return;
    }
    buf[n] = ch;
    buf[n + 1] = L'\0';
    SetWindowTextW(hEdit, buf);
    delete[] buf;
}

void BtnClickParenthesis(HWND hWnd, wchar_t ch) {
    HWND hEdit = GetDlgItem(hWnd, idEd);
    int n = GetWindowTextLengthW(hEdit);
    wchar_t* buf = new wchar_t[n + 2];
    GetWindowTextW(hEdit, buf, n + 1);
    buf[n] = ch;
    buf[n+1] = L'\0';
    SetWindowTextW(hEdit, buf);
    delete[] buf;
}

void BtnClickChangingLanguage(HWND hWnd, int l) {
    HMODULE h=NULL;
    switch (l) {
        case 1:
            h = LoadLibrary(L"C:\\Users\\User\\source\\repos\\Dll2\\Debug\\Dll2.dll");
            if (h == NULL) { MessageBox(NULL, L"Error loading library", L"Error loading library", MB_OK); }
            break;
        case 2:
            h = LoadLibrary(L"C:\\Users\\User\\source\\repos\\Dll4\\Debug\\Dll4.dll");
            if (h == NULL) { MessageBox(NULL, L"Error loading library", L"Error loading library", MB_OK); }
            break;
        default:
            break;
    }
    SetWindowTextW(hWnd, (wchar_t*)GetProcAddress(h, "Name"));
    FreeLibrary(h);
}

/*Основные задачи оконной функции поддерживать в актуальном состоянии то окно приложения, сообщения для которого оно обрабатывает;
Прототип оконной функции :
LRESULT CALLBACK MyWindowProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);
Параметры:
hWnd – дескриптор окна, для которого предназначено сообщение;
uMsg – идентификатор сообщения;
wParam – первый параметр сообщения
lParam – второй параметр сообщения*/
LRESULT CALLBACK MyWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    unsigned int key;
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch (wParam) {
            case VK_DELETE:
                SendMessage(hWnd, WM_COMMAND, idBtn6, 0);
                break;
            case VK_RETURN:
                SendMessage(hWnd, WM_COMMAND, idBtn10, 0);
                break;
            case 0x31:
                SendMessage(hWnd, WM_COMMAND, idBtn1, 0);
                break;
            case 0x30:
                SendMessage(hWnd, WM_COMMAND, idBtn0, 0);
                break;
            case VK_OEM_PLUS:
                SendMessage(hWnd, WM_COMMAND, idBtn2, 0);
                break;
            case VK_OEM_MINUS:
                SendMessage(hWnd, WM_COMMAND, idBtn3, 0);
                break;
            case 0x38:
                SendMessage(hWnd, WM_COMMAND, idBtn4, 0);
                break;
            case VK_OEM_2:
                SendMessage(hWnd, WM_COMMAND, idBtn5, 0);
                break; 
            case VK_BACK:
                SendMessage(hWnd, WM_COMMAND, idBtn7, 0);
                break;
            case VK_ESCAPE:
                SendMessage(hWnd, WM_DESTROY, 0, 0);
                break;
            case 0x51:
                SendMessage(hWnd, WM_COMMAND, idBtn8, 0);
                break;
            case 0x57:
                SendMessage(hWnd, WM_COMMAND, idBtn9, 0);
                break;
            default:
                break;
        }
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED)
            switch (LOWORD(wParam))
            {
                case idBtn0: BtnClickNum(hWnd, L'0');
                    SetFocus(hWnd);
                    break;
                case idBtn1: BtnClickNum(hWnd, L'1');
                    SetFocus(hWnd);
                    break;
                case idBtn2: BtnClickOper(hWnd, L'+');
                    SetFocus(hWnd);
                    break;
                case idBtn3: BtnClickOper(hWnd, L'-');
                    SetFocus(hWnd);
                    break;
                case idBtn4: BtnClickOper(hWnd, L'*');
                    SetFocus(hWnd);
                    break;
                case idBtn5: BtnClickOper(hWnd, L'÷');
                    SetFocus(hWnd);
                    break;
                case idBtn6: BtnClickClean(hWnd);
                    SetFocus(hWnd);
                    break;
                case idBtn7: BtnClickBackspace(hWnd);
                    SetFocus(hWnd);
                    break;
                case idBtn8: BtnClickParenthesis(hWnd, L'(');
                    SetFocus(hWnd);
                    break;
                case idBtn9: BtnClickParenthesis(hWnd, L')');
                    SetFocus(hWnd);
                    break;
                case idBtn10: BtnClickEqually(hWnd);
                    SetFocus(hWnd);
                    break;
                case idBtn11: BtnClickChangingLanguage(hWnd, 1);
                    break;
                case idBtn12: BtnClickChangingLanguage(hWnd, 2);
                    break;
            }
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    /*Точкой входа в программу с графическим интерфейсом пользователя в Windows является функция WinMain (или wWinMain)
    *hInstance – дескриптор экземпляра приложения (или по-другому, дескриптор модуля). Используется ОС для того, чтобы отличать загруженные приложения друг от друга. Требуется некоторым функциям, например, функции загрузки иконки приложения.
    *hPrevInstance – в настоящее время всегда равен NULL. использовался в 16-битных версиях Windows как дескриптор предыдущего экземпляра приложения.
    *pCmdLine – параметры командной строки, переданные приложению (без имени исполняемого модуля приложения).
    *nCmdShow – флаг, который задает способ отображения окна приложения.
    */
    /*Значения параметра nCmdShow также используются функцией ShowWindow(см.далее) :
    *SW_HIDE – спрятать окно приложения и активировать следующее окно(значение константы 0);
    *SW_SHOWNORMAL – активирует и отображает окно; если окно было развернуто или свернуто – восстанавливается его размер и позиция.Рекомендуется использовать это значение при показе окна первый раз при запуске приложения(значение 1);
    *SW_MAXIMIZE – развернуть окно на весь экран(значение 3);
    *SW_MINIMIZE – свернуть окно и активировать следующее окно в Z - порядке(значение 6);
    *SW_RESTORE – активировать и отобразить окно; если окно свернуто или развернуто на весь экран, то функция возвращает его нормальный размер и позицию.Используется для разворачивания свернутого окна(значение 9).
    *SW_SHOW – активировать окно и показать его в текущем состоянии и на текущей позиции(значение 5).
    *SW_SHOWMAXIMIZED – активировать и развернуть на весь экран(значение 3);
    *SW_SHOWMINIMIZED – активировать и  отобразить как свернутое окно(значение 2);
    *SW_SHOWMINNOACTIVE – тоже что и SW_SHOWMINIMIZED, но окно не активируется при отображении(значение 7);
    *SW_SHOWNA – тоже что и SW_SHOW, но окно не активируется при отображении(значение 8);
    *SW_SHOWNOACTIVE – тоже что и SW_SHOWNORMAL, но окно не активируется(значение 4).
    */
    /*Внутри функции WinMain необходимо выполнить следующие действия :
    1) Инициализировать приложение;
    2) Отобразить главное окно приложения.Это включает описание класса окна, его регистрацию, создание окна и его отображение;
    3) Запустить цикл получения и обработки сообщений, который является основой для управления всем приложением.
    */
    HMODULE h = LoadLibrary(L"shell32.dll");
    if (h == NULL) { MessageBox(NULL, L"Error loading library", L"Error loading library", MB_OK); }
    WNDCLASS wcl;//Для описания класса окна используется переменная типа WNDCLASS или WNDCLASSEX:
    wcl.hInstance = hInstance;//Идентифицирует экземпляр приложения, которое будет содержать оконную функцию для данного класса окна
    wcl.lpszClassName = L"MyWindowClass";//Уникальное имя класса окна
    wcl.lpfnWndProc = MyWindowProc;//Указатель на оконную функцию
    wcl.style = CS_HREDRAW | CS_VREDRAW;//Стиль класса окна
    wcl.lpszMenuName = NULL;//Имя ресурса меню по умолчанию
    wcl.hIcon = LoadIcon(h, MAKEINTRESOURCE(181));//Дескриптор пиктограммы приложения.Возможные значения для стандартных пиктограмм : IDI_APPLICATION, IDI_WARNING, IDI_INFORMATION, IDI_ERROR, IDI_QUESTION
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);//Дескриптор курсора(указателя) мыши.
    //Возможные значения для стандартных курсоров : IDC_IBEAM, IDC_CROSS, IDC_WAIT, IDC_HELP, IDC_NO, IDC_UPARROW, IDC_APPSTARTING, IDC_SIZE, IDC_ICON, IDC_SIZENWSE, IDC_SIZENESW, IDC_SIZEWE, IDC_SIZENS, IDC_SIZEALL
    wcl.hbrBackground = (HBRUSH)(1 + COLOR_WINDOW);//Дескриптор кисти(ресурса, с помощью которого осуществляется заполнение объектов на экране).
    //Возможные значения для стандартных кистей : COLOR_APPWORKSPACE, COLOR_BACKGROUND, COLOR_BTNFACE, COLOR_ACTIVECAPTION, COLOR_INACTIVECAPTION, COLOR_CAPTIONTEXT, ...
    wcl.cbClsExtra = 0;//Размер массива дополнительных данных для класса окна(байт)
    wcl.cbWndExtra = 0;//Размер массива дополнительных данных для каждого экземпляра окна(байт)
    FreeLibrary(h);

    /*Для регистрации класса окна используются функции
    *ATOM RegisterClass(const WNDCLASS *lpwc);
    *ATOM RegisterClassEx(const WNDCLASSEX *lpwcx) */
    if (!RegisterClass(&wcl)) {
        return 0;
    }

    /*Для создания окна используются функции
    *HWND CreateWindow(11 параметров);
    *HWND CreateWindowEx(12 параметров); */
    HWND hWnd;
    h = LoadLibrary(L"C:\\Users\\User\\source\\repos\\Dll2\\Debug\\Dll2.dll");
    if (h == NULL) { MessageBox(NULL, L"Error loading library", L"Error loading library", MB_OK); }
    hWnd = CreateWindow(L"MyWindowClass"/* Имя класса окна*/, (wchar_t*)GetProcAddress(h, "Name")/* Заголовок окна*/, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX/*Стиль окна*/, 0, 0,/*Координаты левого верхнего угла*/505, 480,/*Размеры окна*/HWND_DESKTOP/*Дескриптор родительского окна*/, NULL/*Дескриптор главного меню*/, hInstance, NULL/*Указатель на массив дополнительных данных окна*/);
    FreeLibrary(h);
    CreateWindow(L"EDIT", NULL, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | ES_READONLY, 10,10, 470,20, hWnd, (HMENU)idEd, hInstance,NULL);

    CreateWindow(L"BUTTON", L"0", WS_CHILD | WS_BORDER | WS_VISIBLE, 10, 40, 50, 50, hWnd, (HMENU)idBtn0, hInstance, NULL);
    CreateWindow(L"BUTTON", L"1", WS_CHILD | WS_BORDER | WS_VISIBLE, 70, 40, 50, 50, hWnd, (HMENU)idBtn1, hInstance, NULL);
    CreateWindow(L"BUTTON", L"+", WS_CHILD | WS_BORDER | WS_VISIBLE, 130, 40, 50, 50, hWnd, (HMENU)idBtn2, hInstance, NULL);
    CreateWindow(L"BUTTON", L"-", WS_CHILD | WS_BORDER | WS_VISIBLE, 190, 40, 50, 50, hWnd, (HMENU)idBtn3, hInstance, NULL);
    CreateWindow(L"BUTTON", L"*", WS_CHILD | WS_BORDER | WS_VISIBLE, 250, 40, 50, 50, hWnd, (HMENU)idBtn4, hInstance, NULL);
    CreateWindow(L"BUTTON", L"÷", WS_CHILD | WS_BORDER | WS_VISIBLE, 310, 40, 50, 50, hWnd, (HMENU)idBtn5, hInstance, NULL);
    CreateWindow(L"BUTTON", L"С", WS_CHILD | WS_BORDER | WS_VISIBLE, 370, 40, 50, 50, hWnd, (HMENU)idBtn6, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Back", WS_CHILD | WS_BORDER | WS_VISIBLE, 430, 40, 50, 50, hWnd, (HMENU)idBtn7, hInstance, NULL);
    CreateWindow(L"BUTTON", L"(", WS_CHILD | WS_BORDER | WS_VISIBLE, 10, 100, 50, 50, hWnd, (HMENU)idBtn8, hInstance, NULL);
    CreateWindow(L"BUTTON", L")", WS_CHILD | WS_BORDER | WS_VISIBLE, 70, 100, 50, 50, hWnd, (HMENU)idBtn9, hInstance, NULL);
    CreateWindow(L"BUTTON", L"=", WS_CHILD | WS_BORDER | WS_VISIBLE , 130, 100, 50, 50, hWnd, (HMENU)idBtn10, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Ru",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        10, 160, 80, 30, hWnd, (HMENU)idBtn11, hInstance, NULL);
    CreateWindow(L"BUTTON", L"En",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        10, 190, 80, 30, hWnd, (HMENU)idBtn12, hInstance, NULL);

    /*После создания окно нужно отобразить.Для отображения окна используется функция
    *BOOL ShowWindow(HWND hWnd, int nCmdShow);*/
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    //Следующим шагом будет запуск цикла обработки сообщений:
    MSG msg;//структура для представления сообщения
    while (GetMessage(&msg, NULL, 0, 0)) {//обратиться к Windows за очередным сообщением
        TranslateMessage(&msg);//обработать сообщения от клавиатуры
        DispatchMessage(&msg);//переслать сообщение соответствующей оконной функции
    }
    return 0;
}