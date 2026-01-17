#include <iostream>
#include <string>

using namespace std;

class car {

public:

	car() {

	}

	car(car& copy) {
		_mark = copy.get_mark();
		_model = copy.get_model();
		_govID = copy.get_govID();
		_bodyID = copy.get_bodyID();
		_mileage = copy.get_mileage();
	}

	car(string mark, string model, string govid, string bodyid, unsigned int mileage) {
		_mark = mark;
		_model = model;
		set_govID(govid);
		set_bodyID(bodyid);
		_mileage = mileage;
	}

	~car() {

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
			if (id.length() != _govIDlength) {
				throw invalid_argument("[set_govID] Неподходящая длина гос. номера");
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
			size_t bodyid_length = bodyid.length();
			if ((bodyid_length > _bodyIDmaxlength) || (bodyid_length < _bodyIDminlength)) {
				throw invalid_argument("[set_bodyID] Неподходящая длина номера кузова");
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

private:
	string _mark;
	string _model;
	string _govID;
	string _bodyID;
	const unsigned int _govIDlength = 8;
	const unsigned int _bodyIDminlength = 9;
	const unsigned int _bodyIDmaxlength = 12;
	unsigned int _mileage = 0;

};





int main() {

	setlocale(LC_ALL, "Russian");
	
	car test2("Toyota", "Camry", "A123BC39", "123456789ABC", 10000);
	car test3(test2);

	test3.info();
	test2.lower_mileage(1500);
	test2.set_govID("A333AA39");
	test2.set_bodyID("12332332155");
	test2.info();

	car test1("Lada", "Priora", "D4561231", "1", 15000);
}