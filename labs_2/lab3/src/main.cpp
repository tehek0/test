#include "car.h"

int main() {
    srand(time(0));
	setlocale(LC_ALL, "ru_RU.UTF-8");
    car a;
    car b;
    car test = a + b;
    workshop c;
    speaker d;
    d.name = "speaker test 1";
    d.desc = "speaker desc 1";
    d.price = 12;
    c.add_speaker(d);
    d.name = "speaker test 2";
    d.desc = "speaker desc 2";
    d.price = 24;
    c.add_speaker(d);
    d.name = "speaker test 3";
    d.desc = "speaker desc 3";
    d.price = 48;
    c.add_speaker(d);
    d.name = "speaker test 4";
    d.desc = "speaker desc 4";
    d.price = 96;
    c.add_speaker(d);
    c.print_speakers();
    c.attach_car(test);
    c.attach_car(a);
    c.attach_car(b);

    int selector;
    string govid;

    cout << endl << "1) " << test.get_govID() << endl << "2) " << a.get_govID() << endl << "3) " << b.get_govID() << endl << endl;
    cin >> selector;
    cin >> govid;
    c.attach_speaker_to_car(selector, govid);
    c.print_speakers();

    c.get_car_speaker(govid).print();
}
