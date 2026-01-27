#include <car.h>
#include <string>
using namespace std;

unsigned int car::_govIDlength = 6;

bool car::govIDformat(string& govid) {
	if (govid.empty())
		return false;
	size_t govidlen = govid.length();
	if (govidlen != _govIDlength)
		return false;
	for (int i = 0; i < govidlen; ++i) {
		if ((i >= 1) && (i <= 3)) {
			if (govid[i] >= '0' && govid[i] <= '9')
				continue;
			return false;
		}
		if ((isspace(govid[i]) == true) || (ispunct(govid[i]) == true) || (isalpha(govid[i]) == false))
			return false;
	}
	return true;
}

unsigned int car::_mileage = 0;

car::car() {
	cerr << endl << "Запущен стандартный конструктор" << endl;
}

car::car(const car& copy) {
	if (&copy == nullptr) {
		cout << endl << "Указан nullptr в конструкторе копирования" << endl;
		exit(3);
	}
	cerr << endl << "Запущен конструктор копирования" << endl;
	_mark = copy._mark;
	_model = copy._model;
	_govID = copy._govID;
	_bodyID = copy._bodyID;
	_mileage = copy._mileage;
}