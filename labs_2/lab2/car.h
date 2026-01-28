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
	vector<string> _items;
	static unsigned int _govIDlength;
	bool govIDformat(string& govid);


public:

	car();
	car(const car& copy);
	car(string mark, string model, string govid);
	~car();

	string get_mark();
	string get_model();
	string get_govID();
	string get_item(unsigned int id);

	void info();
	void print_items();

	void set_mark(string mark);
	void set_model(string model);
	void set_govID(string id);
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

	car operator+(car& other);
	car operator-(car& other);
	car operator/(car& other);

};

string govIDgenerate();