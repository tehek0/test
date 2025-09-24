#include <iostream>
#include <clocale>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");

    unsigned short h; // unsigned short, т.к. длина не может быть отрицательной и предел short'а достаточно большой для условия поставленной задачи, притом занимает меньше памяти, чем int
    unsigned short a; // см. строку 9
    unsigned short b; // см. строку 9
    unsigned int r; // unsigned int, т.к. длина не может быть отрицательной и максимальный возможный результат уравнения может превысить предел short'а
    
    unsigned short sizeofshort = 8 * sizeof(unsigned short);
    unsigned short sizeofint = 8 * sizeof(unsigned int);
    unsigned short maximumshort = pow(2, sizeofshort) - 1;
    unsigned int maximumint = pow(2, sizeofint) - 1;


    cout << "Использованные типы данных:\nunsigned short - Размер в памяти: "
        << sizeofshort
        << " бит, минимальное значение: 0, максимальное значение: "
        << maximumshort
        << "\nunsigned int - Размер в памяти: "
        << sizeofint
        << " бит, минимальное значение: 0, максимальное значение: "
        << maximumint
        << "\n\n";

    cout << "Высота трапеции: ";
    cin >> h;
    if (h>256) {
        return 0;
    }
    cout << "Нижнее основание трапеции: ";
    cin >> a;
    if (a>1001) {
        return 0;
    }
    cout << "Верхнее основание трапеции: ";
    cin >> b;
    if (b>1001) {
        return 0;
    }
    r = ((a + b) * (int)h) / 2;
    cout << "Площадь трапеции: " << r << endl;
    return r;
}
