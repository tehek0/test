#include <iostream>
#include <string>

using namespace std;

class car {

	const unsigned int _govIDlength = 6;
	const unsigned int _bodyIDminlength = 9;
	const unsigned int _bodyIDmaxlength = 12;

	bool govIDformat(string& govid) {
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

	bool bodyIDformat(string& bodyid) {
		if (bodyid.empty())
			return false;
		size_t bodyidlen = bodyid.length();
		if ((bodyidlen > _bodyIDmaxlength) || (bodyidlen < _bodyIDminlength))
			return false;
		for (int i = 0; i < bodyidlen; ++i) {
			if ((isspace(bodyid[i]) == true) || (ispunct(bodyid[i]) == true) || (isascii(bodyid[i]) == false))
				return false;
		}
		return true;
	}

	string _mark;
	string _model;
	string _govID;
	string _bodyID;
	unsigned int _mileage = 0;

	

public:

	car() {
		cerr << endl << "Запущен стандартный конструктор" << endl;
	}
	
	car(const car& copy) {
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

	car(string mark, string model, string govid, string bodyid, unsigned int mileage) {
		cerr << endl << "Запущен конструктор полного заполнения" << endl;
		_mark = mark;
		_model = model;
		set_govID(govid);
		set_bodyID(bodyid);
		_mileage = mileage;
	}

	~car() {
		cerr << endl << "Запущен деструктор" << endl;
	}

	string get_mark() {
		return _mark;
	}
	string get_model() {
		return _model;
	}
	string get_govID() {
		return _govID;
	}
	string get_bodyID() {
		return _bodyID;
	}
	unsigned int get_mileage() {
		return _mileage;
	}

	void info() {

		cout << endl
			<< "Марка: " << _mark << endl
			<< "Модель: " << _model << endl
			<< "Гос. номер: " << _govID << endl
			<< "Номер кузова: " << _bodyID << endl
			<< "Пробег: " << _mileage << " км."
			<< endl;
	}

	void set_govID(string id) {
		try {
			if (govIDformat(id) == false) {
				throw invalid_argument("[set_govID] Неподходящий формат гос. номера");
			}

			_govID = id;

		}
		catch (invalid_argument& error) {
			cerr << error.what() << endl;
			exit(1);
		}
	}

	void set_bodyID(string bodyid) {
		try {
			if (bodyIDformat(bodyid) == false) {
				throw invalid_argument("[set_bodyID] Неподходящий формат номера кузова");
			}

			_bodyID = bodyid;

		}
		catch (invalid_argument& error) {
			cerr << error.what() << endl;
			exit(2);
		}
	}

	void lower_mileage(unsigned int X) {
		cout << endl << "Некоторые забавные вещи уголовно наказуемы" << endl;

		if (X >= _mileage) {
			_mileage = 0;
			return;
		}

		_mileage -= X;
	}
	
};





int main() {

	setlocale(LC_ALL, "Russian");

	car test1();
	car test2("Toyota", "Camry", "A123BC", "123456789ABC", 10000);
	car test3(test2);

	cout << endl
		<< test3.get_mark() << endl
		<< test3.get_model() << endl
		<< test3.get_govID() << endl
		<< test3.get_bodyID() << endl
		<< test3.get_mileage() << endl;
	test2.lower_mileage(1500);
	test2.set_govID("A333AA");
	test2.set_bodyID("12332332155");
	test2.info();


		string model;
		string mark;
		string govid;
		string bodyid;
		unsigned int mileage;
		 

		cout << endl << "Введите модель: ";
		cin >> model;
		cout << endl << "Введите марку: ";
		cin >> mark;
		cout << endl << "Введите гос. номер (формат: A999AA): ";
		cin >> govid;
		cout << endl << "Введите номер кузова (9-12 символов): ";
		cin >> bodyid;
		cout << endl << "Введите километраж: ";
		cin >> mileage;
		cout << endl << endl << endl << endl << "=== === === Сборка === === ===" << endl;
		car testfinal(mark, model, govid, bodyid, mileage);
		testfinal.info();
	
}