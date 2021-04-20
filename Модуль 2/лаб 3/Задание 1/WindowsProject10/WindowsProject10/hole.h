/***************************************************************
*                                                             *
* Файл     : hole.h                                           *
*                                                             *
* Описание : заголовочный файл с описанием класса             *
*            HOLE (Отверстие)                                 *
*                                                             *
***************************************************************/

#ifndef holeH
#define holeH

#include <windows.h>

#include <vector>
using namespace std;

class HOLE {
private:
    int x, y;         // координаты центра отверстия
    int R;            // радиус отверстия
    unsigned Color;   // цвет отверстия
public:
    HOLE(int x, int y, int R);        // конструктор
    int GetX();                       // прочитать координату Х
    int GetY();                       // прочитать координату Y
    int IsPointInside(int x, int y);   // проверка, лежит ли точка внутри
    void SetSize(int size);           // изменить размер отверстия
    void MoveBy(int dx, int dy);       // сдвинуть отверстие
    void Draw(HDC hDC);               // нарисовать отверстие
    void Erase(HDC hDC);              // стереть отверстие
};

#endif