// вариант 2

#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	short A;
	short Achecker;
	short i;
	bool bitcheck;
	unsigned char lowestbits = 0b11111111;
	cout << "Введите A: ";
	cin >> A;
	Achecker = A & lowestbits;
	cout << "Введите бит i (биты считаем слева направо): ";
	cin >> i;
	bitcheck = (Achecker >> 8 - i) & 1;
	if (bitcheck) {
		cout << "Битовый сдвиг A №1: " << (A = (A >> 1)) << endl;
		cout << "Битовый сдвиг A №2: " << (A = (A >> 1)) << endl;
		cout << "Битовый сдвиг A №3: " << (A = (A >> 1)) << endl;
	}
	else {
		short M;
		cout << "Введите число M: ";
		cin >> M;
		M -= 5;
		(M != 0 ? (cout << (M < 0 ? "M меньше 5 на " : "M больше 5 на ") << M << endl) : (cout << "M равно 5" << endl));
	};
	short N;
	cout << "Введите N (1-7): ";
	cin >> N;
	switch (N) {
	case 1: cout << "Понедельник"; break;
	case 2: cout << "Вторник"; break;
	case 3: cout << "Среда"; break;
	case 4: cout << "Четверг"; break;
	case 5: cout << "Пятница"; break;
	case 6: cout << "Суббота"; break;
	case 7: cout << "Воскресенье"; break;
	default: cout << "Плохой день";
	};

};