#include "car.h"

int main() {
    srand(time(0));
	setlocale(LC_ALL, "Russian");
    car a;
    car b;
    car test = a + b;
    workshop c;
    speaker d;
    d.name = "speaker test";
    d.desc = "speaker desc";
    d.price = 12;
    d.print();
    c.add_speaker(d);
    c.add_speaker(d);
    c.add_speaker(d);
    c.add_speaker(d);
    c.print_speakers();
    c.attach_car(test);
    c.attach_speaker_to_car(0, test.get_govID());
}
