// вариант 2
#include <iostream>
using namespace std;
#include "item2.cpp"
#include "double.cpp"
#include "triple.cpp"

int Item1() {
    cerr << "Running Item 1 Function" << endl;
    int item1_arr[3] = { 0,0,0 };
    cout << "Введите числа: ";
    cin >> item1_arr[0];
    cin >> item1_arr[1];
    cin >> item1_arr[2];
    int result = 0;
    unsigned char counter = 0;
    for (char i = 0; i < 3; ++i) {
        if (item1_arr[i] != 0) {
            ++counter;
        }
    };
    switch (counter)
    {
    case 2:
    {
        result = twonumbers(item1_arr);
        break;
    case 3:
        result = threenumbers(item1_arr);
        break;
    default:
        break;
    }
    return result;
    }
};
    int main() {
        setlocale(LC_ALL, "Russian");
        unsigned short item;
        int main_result;
        cout << "Введите номер пункта: ";
        cin >> item;
        switch (item) {
        case 1:
            main_result = Item1();
            cout << "Функция вернула значение: " << main_result << endl;
            break;
        case 2:
            unsigned short h;
            unsigned short a;
            unsigned short b;
            cout << "Высота трапеции: ";
            cin >> h;
            cout << "Нижнее основание трапеции: ";
            cin >> a;
            cout << "Верхнее основание трапеции: ";
            cin >> b;
            Lab1(h, a, b);
            break;
        default: cerr << "Пункт не найден :("; return 0;
        }
    }



