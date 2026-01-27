#pragma once
#include <string>

using namespace std;

class car {

	unsigned int _govIDlength;
	bool govIDformat(string& govid);
	string _mark;
	string _model;
	string _govID;
	unsigned int _mileage;

public:

	car();
	car(const car& copy);
	car(string mark, string model, string govid, unsigned int mileage);
	~car();

	string get_mark();
	string get_model();
	string get_govID();
	unsigned int get_mileage();

	void info();
	void set_govID(string id);
	void lower_mileage(unsigned int X);

};