#include "field.h"

void Field::init(int size,char def) {
	this->size = size;
	map = new char* [size];
	for (int i = 0; i < size; i++) {
		map[i] = new char[size];
		for (int j = 0; j < size; j++) {
			map[i][j] = def;
		}
	}
}

void Field::paint() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout<<map[i][j];
		}
		cout << endl;
	}
}

void Field::setObject(int i, int j, char object) {
	map[i - 1][j - 1] = object;
}

char Field::getObject(int i, int j) {
	return map[i-1][j-1];
}

void Field::remove() {
	this->~Field();
}

Field::~Field() {
	for (int i = 0; i < size; i++) {
		delete map[i];
	}
	delete[]map;
}