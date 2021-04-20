/***************************************************************
*                                                             *
* Файл     : PlateWindow.cpp                                  *
*                                                             *
* Описание : модуль с реализацией функций,                    *
*            необходимых для создания окна "Пластина"         *
*                                                             *
***************************************************************/
#include "PlateWindow.h"
#include "Plate.h"
#include "Hole.h"
#include <math.h>

// Описание и регистрация класса окна "Пластина"
int RegisterPlateWindow()
{
    WNDCLASS wcl;
    wcl.hInstance = GetModuleHandle(NULL);
    wcl.lpszClassName = L"PlateWindowClass";
    wcl.lpfnWndProc = PlateWindowProc;
    wcl.style = CS_HREDRAW | CS_VREDRAW;
    wcl.lpszMenuName = NULL;
    wcl.hIcon = NULL;
    wcl.hCursor = LoadCursor(NULL, IDC_CROSS);
    wcl.hbrBackground = (HBRUSH)(1 + COLOR_WINDOW);
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    return RegisterClass(&wcl);
}


// Оконная функция внутреннего окна
LRESULT CALLBACK PlateWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Статические локальные переменные, необходимые для работы оконной функции
    static PLATE Plate(200, 200);   // объект-пластина
    static HOLE* LastHole;        // ссылка на некоторый объект-отверстие
    static int LastX, LastY;        // последние координаты мыши
    static enum { NO_OPERATION, CHANGE_SIZE, CHANGE_POS } Mode; // режим работы с объектами

                                                                // извлечь параметры сообщений манипулятора "мышь"
    MouseState ms;
    ExtractMouseParams(wParam, lParam, &ms);

    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint(hWnd, &ps);  // получить контекст устройства
        Plate.Draw(hDC);                  // вызвать метод построения изображения пластины
        EndPaint(hWnd, &ps);              // освободить контекст устройства
        break;
    }

    case WM_LBUTTONDOWN: // нажатие левой кнопки манипулятора "мышь"
                         // создаем объект и начинаем менять его размер
    {
        LastHole = new HOLE(ms.xPos, ms.yPos, 5);  // создаем новый объект-отверстие,
        Plate.AddHole(LastHole);               // добавляем его на пластину
        LastHole->Draw(GetWindowDC(hWnd));     // и сразу же рисуем
        Mode = CHANGE_SIZE; // переходим в режим изменения размера объекта
        break;
    }

    case WM_MBUTTONDOWN: // нажатие средней кнопки манипулятора "мышь"
                         // начинаем менять размер объекта
    {
        LastHole = Plate.GetHoleFromPoint(ms.xPos, ms.yPos); // получим объект под указателем мыши
        if (LastHole != NULL) { // если он есть
            Mode = CHANGE_SIZE;   // переходим в режим изменения размера объекта
        }
        break;
    }

    case WM_RBUTTONDOWN: // нажатие правой кнопки манипулятора "мышь"
                         // начинаем менять положение объекта
    {
        LastHole = Plate.GetHoleFromPoint(ms.xPos, ms.yPos); // получим объект под указателем мыши
        if (LastHole != NULL) { // если он есть
            Mode = CHANGE_POS;    // переходим в режим изменения положения объекта
            LastX = ms.xPos; LastY = ms.yPos;  // запомним координаты курсора
        }
        break;
    }

    case WM_MOUSEMOVE: // перемещение манипулятора "мышь"
    {
        if (LastHole != NULL) // какой-нибудь объект выбран?
            switch (Mode) {     // в каком режиме сейчас находимся?
            case CHANGE_SIZE: // --- режим изменения размера объекта ---
            {
                int r = sqrt(pow(ms.xPos - LastHole->GetX(), 2)     // расчеты нового размера
                    + pow(ms.yPos - LastHole->GetY(), 2));
                LastHole->Erase(GetWindowDC(hWnd));      // стереть
                LastHole->SetSize(r);                    // изменить размер
                LastHole->Draw(GetWindowDC(hWnd));       // нарисовать заново
                break;
            }
            case CHANGE_POS: // --- режим изменения положения объекта ---
            {
                // переместить текущий объект
                LastHole->Erase(GetWindowDC(hWnd));             // стереть
                LastHole->MoveBy(ms.xPos - LastX, ms.yPos - LastY);  // изменить координаты
                LastHole->Draw(GetWindowDC(hWnd));              // нарисовать заново
                                                                // запомнили координаты, куда уже переместили объект
                LastX = ms.xPos; LastY = ms.yPos;
                break;
            }
            }
        break;
    }

    case WM_LBUTTONUP: // отпустили левую кнопку
    case WM_MBUTTONUP: // отпустили среднюю кнопку
    case WM_RBUTTONUP: // отпустили правую кнопку
    {
        Mode = NO_OPERATION; // забыли режим работы
        LastHole = NULL;     // забыли, с каким отверстием работали
        InvalidateRect(hWnd, NULL, false); // обновить окно
        break;
    }

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}


// функция для анализа параметров сообщений манипулятора "мышь"
void ExtractMouseParams(WPARAM wParam, LPARAM lParam, MouseState* ms) {
    // извлечение координат указателя
    ms->xPos = LOWORD(lParam);
    ms->yPos = HIWORD(lParam);
    // анализ состояния кнопок и клавиш
    ms->lButtonPressed = (wParam & MK_LBUTTON) != 0;
    ms->rButtonPressed = (wParam & MK_RBUTTON) != 0;
    ms->mButtonPressed = (wParam & MK_MBUTTON) != 0;
    ms->shiftPressed = (wParam & MK_SHIFT) != 0;
    ms->controlPressed = (wParam & MK_CONTROL) != 0;
}