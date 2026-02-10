#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class car {
private:

	string _mark;
	string _model;
	string _govID;
	string _bodyID;
	vector<string> _items;
	unsigned int _mileage;
	static unsigned int _govIDlength;
	static unsigned int _bodyIDminlength;
	static unsigned int _bodyIDmaxlength;
	bool govIDformat(string& govid);
	bool bodyIDformat(string& bodyid);


public:

	car();
	car(const car& copy);
	car(string mark, string model, string govid, string bodyid, unsigned int _mileage);
	~car();

	string get_mark();
	string get_model();
	string get_govID();
	string get_bodyID();
	string get_item(unsigned int id);
	unsigned int get_mileage();

	void info();
	void print_items();

	void set_mark(string mark);
	void set_model(string model);
	void set_govID(string id);
	void set_bodyID(string id);
	void set_mileage(unsigned int mileage);
	void add_item(string item);
	void add_item(string item, unsigned int id);
	void set_item(unsigned int id, string item);
	void rm_item(string item);
	void rm_item(unsigned int id);
	void copy_items(vector<string>& items);
	void connect_items(car& other);
	void items_sort_by_copies();
	void items_leave_unique();
	void items_leave_common(vector<string>& items);
	void lower_mileage(unsigned int X);

	car operator=(car& other);
	car operator+(car& other);
	car operator-(car& other);
	car operator/(car& other);

};

string govIDgenerate();