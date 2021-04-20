#include <Windows.h>
#include <iostream>

using namespace std;

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
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
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
    WNDCLASS wcl;//Для описания класса окна используется переменная типа WNDCLASS или WNDCLASSEX:
    wcl.hInstance = hInstance;//Идентифицирует экземпляр приложения, которое будет содержать оконную функцию для данного класса окна
    wcl.lpszClassName = L"MyWindowClass";//Уникальное имя класса окна
    wcl.lpfnWndProc = MyWindowProc;//Указатель на оконную функцию
    wcl.style = CS_HREDRAW | CS_VREDRAW;//Стиль класса окна
    wcl.lpszMenuName = NULL;//Имя ресурса меню по умолчанию
    wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);//Дескриптор пиктограммы приложения.Возможные значения для стандартных пиктограмм : IDI_APPLICATION, IDI_WARNING, IDI_INFORMATION, IDI_ERROR, IDI_QUESTION
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);//Дескриптор курсора(указателя) мыши.
    //Возможные значения для стандартных курсоров : IDC_IBEAM, IDC_CROSS, IDC_WAIT, IDC_HELP, IDC_NO, IDC_UPARROW, IDC_APPSTARTING, IDC_SIZE, IDC_ICON, IDC_SIZENWSE, IDC_SIZENESW, IDC_SIZEWE, IDC_SIZENS, IDC_SIZEALL
    wcl.hbrBackground = (HBRUSH)(1 + COLOR_WINDOW);//Дескриптор кисти(ресурса, с помощью которого осуществляется заполнение объектов на экране).
    //Возможные значения для стандартных кистей : COLOR_APPWORKSPACE, COLOR_BACKGROUND, COLOR_BTNFACE, COLOR_ACTIVECAPTION, COLOR_INACTIVECAPTION, COLOR_CAPTIONTEXT, ...
    wcl.cbClsExtra = 0;//Размер массива дополнительных данных для класса окна(байт)
    wcl.cbWndExtra = 0;//Размер массива дополнительных данных для каждого экземпляра окна(байт)

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
    hWnd = CreateWindow(L"MyWindowClass"/* Имя класса окна*/, NULL/* Заголовок окна*/, WS_BORDER | WS_SYSMENU | WS_MAXIMIZEBOX/*Стиль окна*/, 0, 0,/*Координаты левого верхнего угла*/300, 200,/*Размеры окна*/HWND_DESKTOP/*Дескриптор родительского окна*/, NULL/*Дескриптор главного меню*/, hInstance, NULL/*Указатель на массив дополнительных данных окна*/);

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