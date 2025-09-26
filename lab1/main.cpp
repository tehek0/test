#include <iostream>
#include <clocale>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");

    unsigned short h; // unsigned short, т.к. длина не может быть отрицательной и предел short'а достаточно большой для условия поставленной задачи, притом занимает меньше памяти, чем int
    unsigned short a; // см. строку 9
    unsigned short b; // см. строку 9
    float r; // float, т.к. длина не может быть отрицательной и максимальный возможный результат уравнения может превысить предел short'а
    
    unsigned short sizeofshort = 8 * sizeof(unsigned short);
    unsigned short sizeoffloat = 8 * sizeof(float);
    unsigned short maximumshort = pow(2, sizeofshort) - 1;
    short minimumshort = (pow(2,sizeofshort) - maximumshort - 1)*(-1);


    cout << "Использованные типы данных:\nunsigned short - Размер в памяти: "
        << sizeofshort
        << " бит, минимальное значение: "
        << minimumshort
        << ", максимальное значение: "
        << maximumshort
        << "\nfloat - Размер в памяти: "
        << sizeoffloat
        << " бит, минимальное значение: "
        << ""
        << ", максимальное значение: "
        << ""
        << "\n\n";

    cout << "Высота трапеции: ";
    cin >> h;
    cout << "Нижнее основание трапеции: ";
    cin >> a;
    cout << "Верхнее основание трапеции: ";
    cin >> b;
    r = ((a + b) * h) / 2.;
    cout << "Площадь трапеции: " << r << endl;
    return r;
}
