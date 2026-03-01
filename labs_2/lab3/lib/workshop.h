#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class car;

struct speaker {
    string name;
    string desc;
    unsigned int price;
    void print();
};

class workshop {
private:
    string _address;
    vector<speaker> _available_speakers;
    vector<car*> _attached_cars;
public:
    workshop();
    workshop(workshop& other);
    ~workshop();

    void set_address(string& address);
    string get_address();
    void add_speaker(speaker& speaker);
    speaker get_speaker(unsigned int speakerid);
    void print_speakers();
    void attach_car(car& car);
    void attach_speaker_to_car(unsigned int speakerid, string govid);
};