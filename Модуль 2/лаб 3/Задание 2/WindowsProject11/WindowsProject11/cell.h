#include <windows.h>

class Cell {
private:
	unsigned color;
	int left;
	int top;
	int a;
	int figure = 0;
public:
	void setParameters(int left, int top, int a, unsigned color);
	int getLeft();
	int getA();
	int getTop();
	void setFigure(int figure);
	int getFigure();
	void Draw(HDC hdc);
};