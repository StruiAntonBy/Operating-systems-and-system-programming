#include "dictator.h"

void Dictator::init(string name, int sizeField, int numObjects, double costObject, double costRocket) {
	this->name = name;
	this->numObjects = numObjects;
	this->nowNumObjects = numObjects;
	this->costObject = costObject;
	this->costRocket = costRocket;

	field.init(sizeField, EmptyCell);

	for (int i = 0; i < numObjects; i++) {
		int x, y;
		cout<<"Введите координаты объекта "<<i+1<<" :"<<endl;
		cin >> x;
		cin >> y;

		if (x<0 || x>sizeField || y<0 || y>sizeField || field.getObject(x, y) == Object) {
			i -= 1;
			cout<<"Неправильные координаты"<<endl;
			continue;
		}

		field.setObject(x, y, Object);
	}
}

string Dictator::getName() {
	return name;
}

int Dictator::getNumRocketsUsed() {
	return numRocketsUsed;
}

void Dictator::addRocketUsed() {
	numRocketsUsed += 1;
}

void Dictator::destroyObject() {
	nowNumObjects -= 1;
}

void Dictator::paint() {
	field.paint();
	cout<<name<<endl;
}

double Dictator::getCostObject() {
	return costObject;
}

double Dictator::getCostRocket() {
	return costRocket;
}

int Dictator::getNumObjects() {
	return numObjects;
}

void Dictator::remove() {
	field.remove();
}

int Dictator::getNowNumObjects() {
	return nowNumObjects;
}

Dictator::~Dictator() {
	field.remove();
}