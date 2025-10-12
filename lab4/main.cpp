// вариант 2

#include <iostream>
using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	const char ArrLen = 2 + 3;
	int Arr[ArrLen];
	char SummUp25 = 0;

	for (char i = 0; i < ArrLen; ++i) {
		cout << "Введите элемент массива №" << i + 1 << ": ";
		cin >> Arr[i];
		int SummCheck = Arr[i];
		int Summ = 0;
		while ((SummCheck >= 0 ? SummCheck : SummCheck * (-1)) > 0) {
			Summ += SummCheck % 10;
			SummCheck /= 10;
		}
		if (Summ > 25)
			++SummUp25;
	}

	if (SummUp25 >= 2) {
		for (char i = 0; i < ArrLen - 1; ++i) {
			for (char j = i + 1; j < ArrLen; ++j) {
				if (Arr[i] > Arr[j]) {
					int tmp = Arr[i];
					Arr[i] = Arr[j];
					Arr[j] = tmp;
				}
			}
		}
	}

	cout << "Массив: ["
		<< Arr[0] << ", "
		<< Arr[1] << ", "
		<< Arr[2] << ", "
		<< Arr[3] << ", "
		<< Arr[4] << "]" << endl;

	const char MatRow = 3;
	const char MatCol = 4;

	int Mat[MatRow][MatCol];
	char ArrHasPositives[MatCol];
	for (char i = 0; i < MatCol; ++i) {
		char HasPositives = 0;
		for (char j = 0; j < MatRow; ++j)
		{
			cout << "Введите элемент матрицы столбца " << i + 1 << ", строки " << j + 1 << ": ";
			cin >> Mat[j][i];
			if (Mat[j][i] >= 0)
				++HasPositives;
		}
		ArrHasPositives[i] = HasPositives;
	}
	cout << endl << "Массив количества положительных чисел в столбцах: ";
	for (char j = 0; j < MatCol; ++j)
	{
		short getchar = ArrHasPositives[j];
		cout << getchar << " ";
	}
	cout << endl << endl;

	if ((ArrHasPositives[0] == ArrHasPositives[1]) && (ArrHasPositives[1] == ArrHasPositives[2]) && (ArrHasPositives[2] == ArrHasPositives[3])) {
		cout << "Матрица: ";
		for (char i = 0; i < MatRow; ++i) {
			cout << endl;
			for (char j = 0; j < MatCol; ++j)
			{
				cout << Mat[i][j] << " ";
			}
		}
		return 1;
	}

	char SelectCol = 0;
	for (char i = 1; i < MatCol; ++i) {
			if ((ArrHasPositives[i] < ArrHasPositives[SelectCol]))
				SelectCol = i;
	}
	for (char i = 0; i < MatRow; ++i) {
		Mat[i][SelectCol] = 100;
	}

	cout << "Матрица: ";
	for (char i = 0; i < MatRow; ++i) {
		cout << endl;
		for (char j = 0; j < MatCol; ++j)
		{
			cout << Mat[i][j] << " ";
		}
	}
	return 2;
}
