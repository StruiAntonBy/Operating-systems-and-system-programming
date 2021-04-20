/***************************************************************
*                                                             *
* Файл     : plate.h                                          *
*                                                             *
* Описание : заголовочный файл с описанием класса             *
*            PLATE (Пластина)                                 *
*                                                             *
***************************************************************/

#ifndef PlateH
#define PlateH

#include <windows.h>

#include <vector>
using namespace std;

#include "Hole.h"

class PLATE {
private:
    int width, height;                     // размеры пластины
    vector<HOLE*> Hole;                   // список отверстий
public:
    PLATE(int width, int height);          // конструктор
    void AddHole(HOLE* Hole);             // добавить отверстие на пластину
    HOLE* GetHoleFromPoint(int x, int y);   // определить отверстие по координате
    void Draw(HDC hDC);                    // нарисовать пластину с отверстиями
};

#endif
