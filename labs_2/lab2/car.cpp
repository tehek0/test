#include "car.h"

unsigned int car::_govIDlength = 6;

inline bool car::govIDformat(string& govid) {
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
		if ((isspace(govid[i]) == 1) || (ispunct(govid[i]) == 1) || (isalpha(govid[i]) == false))
			return false;
	}
	return true;
}

car::car() :
	_mark("Default"),
	_model("Default"),
	_govID("D123EF"),
	_items{ "default1", "default2" }
{
	cerr << endl << "Запущен стандартный конструктор" << endl;
}

car::car(const car& copy)
{
	if (&copy == nullptr) {
		cout << endl << "Указан nullptr в конструкторе копирования" << endl;
		exit(3);
	}
	cerr << endl << "Запущен конструктор копирования" << endl;
	_mark = copy._mark;
	_model = copy._model;
	_govID = copy._govID;
	_items = copy._items;
}

car::car(string mark, string model, string govid)
{
	cerr << endl << "Запущен конструктор полного заполнения" << endl;
	_mark = mark;
	_model = model;
	set_govID(govid);
	_items = {};
}

car::~car()
{
	cerr << endl << "Запущен деструктор" << endl;
}

string car::get_mark() {
	return _mark;
}
string car::get_model() {
	return _model;
}
string car::get_govID() {
	return _govID;
}
string car::get_item(unsigned int id) {
	return _items[id];
}

void car::info() {
	cout << endl
		<< "Марка: " << _mark << endl
		<< "Модель: " << _model << endl
		<< "Гос. номер: " << _govID << endl
		<< "Багаж: ";
	print_items();
	cout << endl;
}

void car::print_items() {
	size_t size = _items.size();
	cout << "{ ";
	for (int i = 0; i < size; ++i) {
		cout << _items[i] << " ";
	}
	cout << "}";
}

void car::set_mark(string mark) {
	_mark = mark;
}
void car::set_model(string model) {
	_model = model;
}
void car::set_govID(string id) try {
	if (govIDformat(id) == false) {
		throw invalid_argument("[set_govID] Неподходящий формат гос. номера");
	}

	_govID = id;

}
catch (invalid_argument& error) {
	cerr << error.what() << endl;
	exit(1);
}
void car::add_item(string item) {
	_items.reserve(_items.size());
	_items.push_back(item);
}
void car::add_item(string item, unsigned int id) {
	try {
		if (_items.size() < id) {
			throw invalid_argument("[set_item] Выход за пределы вектора");
		}
		_items.reserve(_items.size() + 1);
		_items.insert(_items.begin() + id, item);
	}
	catch (invalid_argument& error) {
		cerr << error.what() << endl;
		exit(2);
	}
	
}
void car::set_item(unsigned int id, string item) {
	try {
		if (_items.size() < id) {
			throw invalid_argument("[set_item] Выход за пределы вектора");
		}
		_items[id] = item;
	}
	catch (invalid_argument& error) {
		cerr << error.what() << endl;
		exit(3);
	}
}
void car::rm_item(string item) {
	for (size_t i = 0; i < _items.size(); ++i) {
		if (_items[i] == item) {
			_items.erase(_items.begin() + i);
			_items.shrink_to_fit();
			return;
		}
	}
}
void car::rm_item(unsigned int id) {
	try {
		if (_items.size() < id) {
			throw invalid_argument("[rm_item] Выход за пределы вектора");
		}
		_items.erase(_items.begin() + id);
		_items.shrink_to_fit();
	}
	catch (invalid_argument& error) {
		cerr << error.what() << endl;
		exit(4);
	}
}

void car::copy_items(vector<string>& items) {
	_items = items;
}

void car::connect_items(car& other) {
	size_t size = other._items.size();
	for (size_t i = 0; i < size; ++i) {
		this->add_item(other._items[i]);
	}
}

void car::items_sort_by_copies() {
	size_t size = _items.size();
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = i + 1; j < size; ++j) {
			if (_items[i] == _items[j]) {
				string temp = _items[j];
				_items.erase(_items.begin() + j);
				_items.insert(_items.begin() + i, temp);
			}
		}
	}
}

void car::items_leave_unique() {
	size_t size = _items.size();
	for (size_t i = 0; i < size; ++i) {
		bool flag = false;
		for (size_t j = i + 1; j < size; ++j) {
			if (_items[i] == _items[j]) {
				flag = true;
				_items.erase(_items.begin() + j);
				_items.shrink_to_fit();
				--size;
				--j;
			}

		}
		if (flag == true) {
			_items.erase(_items.begin() + i);
			_items.shrink_to_fit();
			--size;
			--i;
		}
		
	}
}

void car::items_leave_common(vector<string>& items) {
	size_t size_this = _items.size();
	size_t size_other = items.size();
	for (size_t i = 0; i < size_this; ++i) {
		bool flag = false;
		for (size_t j = 0; j < size_other; ++j) {
			if (_items[i] == items[j]) {
				flag = true;
				items.erase(items.begin() + j);
				items.shrink_to_fit();
				--size_other;
				break;
			}
		}
		if (flag == false) {
			_items.erase(_items.begin() + i);
			_items.shrink_to_fit();
			--size_this;
			--i;
		}
	}
}

car car::operator+(car& other){
	car result;
	srand(time(0));
	int random = rand() % 2;
	switch (random) {
	case 0:
		result.set_mark(this->get_mark());
		result.set_model(this->get_model());
		break;
	case 1:
		result.set_mark(other.get_mark());
		result.set_model(other.get_model());
		break;
	}
	result.set_govID(govIDgenerate());

	this->connect_items(other);
	this->items_sort_by_copies();
	result.copy_items(this->_items);

	return result;
}

car car::operator-(car& other) {
	car result;
	srand(time(0));
	int random = rand() % 2;
	switch (random) {
	case 0:
		result.set_mark(this->get_mark());
		result.set_model(other.get_model());
		break;
	case 1:
		result.set_mark(other.get_mark());
		result.set_model(this->get_model());
		break;
	}
	result.set_govID(govIDgenerate());

	this->connect_items(other);
	this->items_leave_unique();
	result.copy_items(this->_items);

	return result;
}

car car::operator/(car& other) {
	car result;
	srand(time(0));
	int random = rand() % 2;
	switch (random) {
	case 0:
		result.set_mark(this->get_mark());
		break;
	case 1:
		result.set_mark(other.get_mark());
		break;
	}
	result.set_model(this->get_model());
	result.set_govID(govIDgenerate());

	this->items_leave_common(other._items);
	result.copy_items(this->_items);

	return result;
}


string govIDgenerate() {

	string newid = "";
	string alpha = "ABEKMHOPCTYX";
	string numbers = "0123456789";
	
	int randomid = rand() % 12;
	newid += alpha[randomid];
	for (int i = 0; i < 3; ++i) {
		randomid = rand() % 10;
		newid += numbers[randomid];
	}
	for (int i = 0; i < 2; ++i) {
		randomid = rand() % 12;
		newid += alpha[randomid];
	}

	return newid;
}