#include <math.h>
#include "cell.h"
#include "figure.h"

class Board {
private:
	Cell arr[8][8];
	Figure figureBlack, figureWhite;
	int SizeCell;
public:
	Board(int SizeCell);
	void Draw(HDC hdc);
	int takeFigure(HDC hdc,int x, int y);
	bool setFigure(HDC hdc,int x, int y,int figure);
	void deleteFigure(HDC hdc, int x, int y);
};