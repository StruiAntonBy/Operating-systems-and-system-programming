#include "cell.h"

void Cell::setParameters(int left, int top, int a, unsigned color) {
	this->top = top;
	this->left = left;
	this->a = a;
	this->color = color;
}

int Cell::getA() {
	return a;
}

int Cell::getLeft() {
	return left;
}

int Cell::getTop() {
	return top;
}

int Cell::getFigure() {
	return figure;
}

void Cell::setFigure(int figure) {
	this -> figure = figure;
}

void Cell::Draw(HDC hdc) {
	RECT rect;
	SetRect(&rect, left, top, left+a, top+a);
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH old=(HBRUSH)SelectObject(hdc, hBrush);
	FillRect(hdc, &rect, hBrush);
	DeleteObject(SelectObject(hdc, old));
}