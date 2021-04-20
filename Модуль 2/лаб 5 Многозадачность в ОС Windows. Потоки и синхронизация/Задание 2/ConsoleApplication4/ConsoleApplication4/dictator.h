#include "field.h"
#include <string>
#include <Windows.h>
#include <ctime>
#define EmptyCell '.'
#define Object '#'
#define DestroyedCell 'O'
#define DestroyedObject '&'

class Dictator {
private:
	string name;
	int numObjects; 
	int nowNumObjects;
	double costObject; 
	double costRocket; 
	int numRocketsUsed = 0;
public:
	Field field;
	void init(string name, int sizeField, int numObjects, double costObject, double costRocket);
	void paint();
	void remove();
	double getCostObject();
	double getCostRocket();
	string getName();
	int getNumRocketsUsed();
	void addRocketUsed();
	int getNumObjects();
	int getNowNumObjects();
	void destroyObject();
	~Dictator();
};