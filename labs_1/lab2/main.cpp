// вариант 2

#include <iostream>
#include <bitset>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	short A;
	short Achecker;
	short i;
	bool bitcheck;
	cout << "Введите A: ";
	cin >> A;
	Achecker = A;
	cout << bitset<8>(Achecker) << endl;
	cout << "Введите бит i (биты считаем слева направо): ";
	cin >> i;
	bitcheck = (Achecker >> 8 - i) & 1;
	if (bitcheck == 1) {
		cout << "Битовый сдвиг A №1: " << (A = (A >> 1)) << " = " << bitset<8>(A) << endl;
		cout << "Битовый сдвиг A №2: " << (A = (A >> 1)) << " = " << bitset<8>(A) << endl;
		cout << "Битовый сдвиг A №3: " << (A = (A >> 1)) << " = " << bitset<8>(A) << endl;
	}
	else {
		short M;
		cout << "Введите число M: ";
		cin >> M;
		M -= 5;
		(M != 0 ? (cout << (M < 0 ? "M меньше 5 на " : "M больше 5 на ") << (M < 0 ? -M : M) << endl) : (cout << "M равно 5" << endl));
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