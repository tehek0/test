#include "workshop.h"
#include "../src/car.h"

using namespace std;

workshop::workshop() {
    _address = "Default Address";
    _available_speakers = {};
    _attached_cars = {};
    cout << endl << "Запущен стандартный конструктор workshop" << endl;
}

workshop::workshop(workshop& other) {
    if (&other == nullptr) {
		cout << endl << "Указан nullptr в конструкторе копирования workshop" << endl;
		exit(3);
	}
    _address = other._address;
    _available_speakers = other._available_speakers;
    _attached_cars = other._attached_cars;
    cout << endl << "Запущен конструктор копирования workshop" << endl;
}

workshop::~workshop() {
    _available_speakers.clear();
	_available_speakers.shrink_to_fit();
    _attached_cars.clear();
	_attached_cars.shrink_to_fit();
	cerr << endl << "Запущен деструктор workshop" << endl;
}

void workshop::set_address(string& address) {
    _address = address;
}

string workshop::get_address() {
    return _address;
}

void workshop::add_speaker(speaker& speaker) {
    _available_speakers.reserve(_available_speakers.size());
	_available_speakers.push_back(speaker);
}

speaker workshop::get_speaker(unsigned int speakerid) {
    try {
		if (_available_speakers.size() < speakerid) {
			throw invalid_argument("[get_speaker] Выход за пределы вектора");
		}
		return _available_speakers[speakerid];
	}
	catch (invalid_argument& error) {
		cerr << error.what() << endl;
		exit(4);
	}
}

void speaker::print() {
    cout << this->name << ":" << endl 
        << "- Описание: " << this->desc << endl
        << "- Цена: " << this->price << endl;
}

void workshop::print_speakers() {
	size_t size = _available_speakers.size();
	cout << "[\n";
	for (int i = 0; i < size; ++i) {
		cout << i << ") ";
        _available_speakers[i].print();
	}
	cout << "]";

}

void workshop::attach_car(car& car) {
    _attached_cars.reserve(_attached_cars.size());
    _attached_cars.push_back(&car);
}

void workshop::attach_speaker_to_car(unsigned int speakerid, string govid) {
    try {
		if (_available_speakers.size() < speakerid) {
			throw invalid_argument("[attach_speaker_to_car] Выход за пределы вектора");
		}
	}
	catch (invalid_argument& error) {
		cerr << error.what() << endl;
		exit(4);
	}

    for (int i = 0; i < _attached_cars.size(); ++i) {
        car& temp = *_attached_cars[i];
        if (temp._govID == govid) {
            _attached_cars[i]->_speaker = _available_speakers[speakerid];
            _available_speakers.erase(_available_speakers.begin() + speakerid);
            return;
        } else {
            continue;
        }
    }
    cerr << "[attach_speaker_to_car] Не найдена машина с номером \"" << govid << "\"";
    exit(5);
}

speaker workshop::get_car_speaker(string govid) {
    for (int i = 0; i < _attached_cars.size(); ++i) {
        car& temp = *_attached_cars[i];
        if (temp._govID == govid) {
            return temp._speaker;
        } else {
            continue;
        }
    }
    cerr << "[get_car_speaker] Не найдена машина с номером \"" << govid << "\"";
    exit(5);
}

void workshop::print_cars() {
	size_t size = _attached_cars.size();
	cout << "[\n";
	for (int i = 0; i < size; ++i) {
		cout << i << ") ";
        (_attached_cars[i])->info();
	}
	cout << "]";

}
