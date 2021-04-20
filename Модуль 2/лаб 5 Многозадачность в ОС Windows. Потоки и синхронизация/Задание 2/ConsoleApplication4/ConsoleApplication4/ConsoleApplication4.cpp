#include "dictator.h"
#define Aim '+'
#define NameDictator1 "Федерико"
#define NameDictator2 "Эрнандо"
#define SizeField 5

Dictator a, b;
HANDLE hEventA = NULL;
HANDLE hEventB= NULL;

void paint() {
	a.paint();
	cout << endl;
	b.paint();
	cout << endl;
}

int getRandomNum() {
	srand(static_cast<unsigned int>(GetTickCount()));
	return rand() % SizeField + 1;
}

int attack(Dictator& dict1, Dictator& dict2) {
	if (dict1.getNowNumObjects() == 0) {
		paint();
		cout << dict2.getName() << " уничтожил все цели" << endl;
		return 0;
	}


	if (dict2.getNumObjects() * dict2.getCostObject() < dict1.getCostRocket() * dict1.getNumRocketsUsed()) {
		paint();
		cout << dict1.getName() << " израсходовал слишком много снарядов" << endl;
		return 0;
	}

	int x = getRandomNum();
	paint();
	Sleep(1000);
	system("cls");
	int y = getRandomNum();

	char prev = dict2.field.getObject(x, y);
	dict2.field.setObject(x, y, Aim);
	paint();
	Sleep(1000);
	system("cls");

	dict1.addRocketUsed();
	switch (prev) {
	case EmptyCell:
		dict2.field.setObject(x, y, DestroyedCell);
		break;
	case Object:
		dict2.destroyObject();
		dict2.field.setObject(x, y, DestroyedObject);
		break;
	default:
		dict2.field.setObject(x, y, prev);
		break;
	}
	paint();
	Sleep(500);
	return 1;
}

DWORD WINAPI thread1(LPVOID t) { // Федерико
	for (;;) {
		WaitForSingleObject(hEventA, INFINITE);
		system("cls");
		switch (attack(a, b)) {
			case 0:
				return 0;
			case 1:
				break;
		}
		SetEvent(hEventB);
		ResetEvent(hEventA);
	}
	return 0;
}

DWORD WINAPI thread2(LPVOID t) { // Эрнандо
	for (;;) {
		WaitForSingleObject(hEventB, INFINITE);
		system("cls");

		switch (attack(b, a)) {
			case 0:
				return 0;
			case 1:
				break;
		}

		SetEvent(hEventA);
		ResetEvent(hEventB);
	}
	return 0;
}

int main() {
	setlocale(0, "");
	hEventA = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEventB = CreateEvent(NULL, FALSE, FALSE, NULL);
	int costObject, costRocket, numObjects;
	
	cout<<"Диктатор " <<NameDictator1<<endl;
	cout << "Введите количество объектов:";
	cin >> numObjects;
	cout << "Введите стоимость объекта:";
	cin >> costObject;
	cout << "Введите стоимость снаряда:";
	cin >> costRocket;

	if (pow(SizeField, 2) < numObjects || numObjects < 0 || costObject<0 || costRocket<0) {
		cout << "Некорректный ввод данных" << endl;
		return 1;
	}

	a.init(NameDictator1, SizeField, numObjects, costObject, costRocket);

	cout << "Диктатор "<<NameDictator2 << endl;
	cout << "Введите количество объектов:";
	cin >> numObjects;
	cout << "Введите стоимость объекта:";
	cin >> costObject;
	cout << "Введите стоимость снаряда:";
	cin >> costRocket;

	if (pow(SizeField, 2) < numObjects || numObjects < 0 || costObject < 0 || costRocket < 0) {
		cout << "Некорректный ввод данных" << endl;
		return 1;
	}

	b.init(NameDictator2, SizeField, numObjects, costObject, costRocket);

	system("cls");

	HANDLE hThreads[2];
	hThreads[0] = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, thread2, NULL, 0, NULL);

	SetEvent(hEventA);

	DWORD dwWaitResult = WaitForMultipleObjects(2, hThreads, FALSE, INFINITE);

	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);
	a.remove();
	b.remove();

	return 0;
}