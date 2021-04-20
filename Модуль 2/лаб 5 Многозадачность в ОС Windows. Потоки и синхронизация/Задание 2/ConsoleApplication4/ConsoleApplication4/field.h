#include <iostream>
using namespace std;

class Field {
private:
	int size;
	char **map;
public:
	void init(int size, char def);
	void remove();
	void setObject(int i, int j, char object);
	char getObject(int i, int j);
	void paint();
	~Field();
};