/***************************************************************
*                                                             *
* Файл     : hole.cpp                                         *
*                                                             *
* Описание : модуль с реализацией методов класса              *
*            HOLE (Отверстие)                                 *
*                                                             *
***************************************************************/

#include "hole.h"

#include <math.h>
#include <stdlib.h>
#include <random>

// конструктор
HOLE::HOLE(int x, int y, int R) {
    random_device rd;
    mt19937 gen(rd());
    this->x = x;
    this->y = y;
    this->R = R;
    this->Color = gen();
}

// прочитать координату Х
int HOLE::GetX() {
    return x;
}

// прочитать координату Y
int HOLE::GetY() {
    return y;
}

// проверка, лежит ли точка внутри отверстия
int HOLE::IsPointInside(int x, int y) {
    if (pow(x - this->x, 2) + pow(y - this->y, 2) <= R * R) {
        return 1;
    }
    else {
        return 0;
    }
}

// изменить размер отверстия
void HOLE::SetSize(int size) {
    R = size;
}

// сдвинуть отверстие
void HOLE::MoveBy(int dx, int dy) {
    x += dx;
    y += dy;
}

// нарисовать отверстие
void HOLE::Draw(HDC hDC) {
    // создание новых GDI-объектов,
    // загрузка их в контекст устройства,
    // запоминание исходных GDI-объектов
    HPEN oldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, Color));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, CreateSolidBrush(Color));
    Ellipse(hDC, x - R, y - R, x + R + 1, y + R + 1);
    // восстановление исходных GDI-объектов,
    // удаление ранее созданных GDI-объектов
    DeleteObject(SelectObject(hDC, oldPen));
    DeleteObject(SelectObject(hDC, oldBrush));
}

// стереть отверстие
void HOLE::Erase(HDC hDC) {
    // рисуем белым цветом
    SelectObject(hDC, GetStockObject(WHITE_PEN));
    SelectObject(hDC, GetStockObject(WHITE_BRUSH));
    Ellipse(hDC, x - R, y - R, x + R + 1, y + R + 1);
}