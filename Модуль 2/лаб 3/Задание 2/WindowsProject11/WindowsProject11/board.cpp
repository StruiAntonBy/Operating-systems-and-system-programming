#include "board.h"

#define white RGB(255,255,255);
#define black_board RGB(79,79,79);
#define black_figure RGB(0,0,0);

Board::Board(int SizeCell) {
	this->SizeCell = SizeCell;
}

int Board::takeFigure(HDC hdc,int x, int y) { // 0 - нет 1 - черная 2 - белая
    int bx1 = (8 * SizeCell) + 30;
    int by1 = (3 * SizeCell) + 10;
    int bx2 = bx1 + SizeCell;
    int by2 = by1 + SizeCell;

    int wx1 = bx1;
    int wy1 = by1 + SizeCell;
    int wx2 = bx2;
    int wy2 = wy1 + SizeCell;

    if (x >= bx1 && x <= bx2 && y >= by1 && y <= by2) {
        return 1;
    }
    else if (x >= wx1 && x <= wx2 && y >= wy1 && y <= wy2) {
        return 2;
    }
    else {
        int j = ceil((x - 10) / SizeCell);
        int i = ceil((y - 10) / SizeCell);
        int figure = arr[i][j].getFigure();
        if (figure!=0) {
            arr[i][j].Draw(hdc);
            arr[i][j].setFigure(0);
            return figure;
        }
        else {
            return 0;
        }
    }
}


bool Board::setFigure(HDC hdc,int x, int y,int figure) {
    int j = ceil((x-10) / SizeCell);
    int i = ceil((y-10) / SizeCell);
    if (i < 3 || i>4) {
        unsigned color;

        switch (figure) {
            case 1:
                color = black_figure;
                break;
            case 2:
                color = white;
                break;
        }

        if (arr[i][j].getFigure()==0) {
            if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
                int a = arr[i][j].getA();
                int left = arr[i][j].getLeft();
                int top = arr[i][j].getTop();
                Figure f;
                f.setParameters(left, top, a, color);
                f.Draw(hdc);
                arr[i][j].setFigure(figure);
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void Board::deleteFigure(HDC hdc, int x, int y) {
    int j = ceil((x - 10) / SizeCell);
    int i = ceil((y - 10) / SizeCell);
    if (arr[i][j].getFigure()!=0) {
        arr[i][j].setFigure(0);
        arr[i][j].Draw(hdc);
    }
}

void Board::Draw(HDC hdc) {
    unsigned color=black_figure;
    Cell cell;
    cell.setParameters(0, 0, (SizeCell * 8)+20, color);
    cell.Draw(hdc);

    figureBlack.setParameters((8* SizeCell)+30,(3* SizeCell) +10, SizeCell,color);
    figureBlack.Draw(hdc);

    color = white;
    figureWhite.setParameters((8 * SizeCell) + 30, (4 * SizeCell) + 10, SizeCell, color);
    figureWhite.Draw(hdc);

    int left = 10;
    int top = 10;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
                color = black_board;
            }
            else {
                color = white;
            }
            arr[i][j].setParameters(left, top, SizeCell, color);
            left += SizeCell;
            arr[i][j].Draw(hdc);
        }
        left = 10;
        top += SizeCell;
    }
}