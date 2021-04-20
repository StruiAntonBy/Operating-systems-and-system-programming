#include "figure.h"

void Figure::setParameters(int x, int y, int a, unsigned color) {
	this->x = x;
	this->y = y;
	this->a = a;
	this->color = color;
}

void Figure::Draw(HDC hdc) {
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x, y, x+a, y+a);
	DeleteObject(hBrush);
}