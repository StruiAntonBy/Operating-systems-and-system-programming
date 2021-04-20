#include <windows.h>

class Figure {
private:
	unsigned color;
	int x, y;
	int a;
public:
	void setParameters(int x, int y, int a, unsigned color);
	void Draw(HDC hdc);
};