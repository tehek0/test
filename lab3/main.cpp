// вариант 2

#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	
	int N;
	int Element = 0;

	int Mult3 = 1;
	int Min3 = 1<<(((sizeof(int))*8)-2);
	int Min3N = 0;
	bool Had3 = false;

	cout << "Введите кол-во эл-ов N: ";
	cin >> N;
	cout << endl;

	for (int N_count = 1; N_count <= N; ++N_count) {

		cout << "Введите элемент №" << N_count << ": ";
		cin >> Element;
		cout << endl;

		if ((Element % 10) != 3)
			continue;

		Had3 = true;
		Mult3 *= Element;
		if (Min3 >= Element) {
			Min3 = Element;
			Min3N = N_count;
			}

	}

	if (Had3 == false) {
		cout << "Нет элементов, соответствующих условию :/" 
			<< endl;
	}
	else {
		cout << "Произведение элементов последовательности, оканчивающихся на 3: " 
			<< Mult3 
			<< endl << "Минимальный элемент последовательности, оканчивающийся на 3: №" 
			<< Min3N 
			<< " со значением " 
			<< Min3 
			<< endl;
	}

	unsigned short X;
	cout << "Введите X: ";
	cin >> X;
	cout << endl;

	unsigned short X_sum = 0;
	do {
		X_sum += X % 10;
		X /= 10;
	} while (X > 0);

	cout << "Сумма цифр числа: " << X_sum << endl;

}