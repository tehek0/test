#include "car.h"

void review() {
    cout << "Интерес: 7/10" << endl
    << "Наполненность: 10/10" << endl
    << "Сложность: 9/10" << endl << endl;
}

int main() {
    srand(time(0));
	setlocale(LC_ALL, "ru_RU.UTF-8");
    review();
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
    c.attach_car(test);
    c.attach_car(a);
    c.attach_car(b);

    

    int selector;
    string govid;

    while (true) {
    c.print_speakers();
    cout << endl << "Выберите колонку по id: ";
    cin >> selector;
    c.print_cars();
    cout << endl << "Выберите машину по гос. номеру: ";
    cin >> govid;
    c.attach_speaker_to_car(selector, govid);

    cout << endl << endl;
    c.get_car_speaker(govid).print();
    cout << endl << endl;
    }
}
