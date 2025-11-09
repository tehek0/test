// Вариант 2
#include <iostream>
using namespace std;

int counter = 0;
int* get_zeros(int** memory, int col, int row) {
	int* arr = static_cast<int*>(calloc(row * col, 4));
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			if (memory[j][i] == 0) {
				arr[counter] = i;
				++counter;
			}
		}
	}
	return arr;

}

void read_memory(int** memory, int col, int row) {
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			cout << memory[j][i] << " ";
		}
		cout << endl;
	}
}

void item1() {
	const char base_row = 2;
	const char base_col = 2;
	int base[base_row][base_col];

	cout << "Введите A строк для добавления вверх: ";
	cin >> base[0][0];
	cout << "Введите B строк для добавления влево: ";
	cin >> base[1][0];
	cout << "Введите коэфициент C: ";
	cin >> base[0][1];
	cout << "Введите коэфициент Д: ";
	cin >> base[1][1];

	int row = (base_row + base[1][0]);
	int col = (base_col + base[0][0]);
	int indexes = row * col;
	int** memory = (int**)calloc(row, sizeof(int*));
	for (int i = 0; i < row; ++i) {
		memory[i] = (int*)calloc(col, sizeof(int));
	}

	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {

			memory[j][i] = ((i * base[0][1]) + (j * base[1][1]));
			if ((i == col - 1) && (j == row - 1)) {
				memory[j - 1][i - 1] = base[0][0];
				memory[j - 1][i] = base[0][1];
				memory[j][i - 1] = base[1][0];
				memory[j][i] = base[1][1];
			}
		}

	}

	int new_col = 0;
	int** new_memory = (int**)calloc(row, sizeof(int*));
	for (int i = 0; i < row; ++i) {
		new_memory[i] = (int*)calloc(col - counter, sizeof(int));
	}
	int* zero_array = get_zeros(memory, col, row);
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			bool allow = 1;
			for (int k = 0; k < counter; ++k) {
				if (i == zero_array[k]) {
					allow = 0;
				}
			}
			if (allow != 1) {
				--new_col;
				break;
			}
			new_memory[j][new_col] = memory[j][i];
		}
		++new_col;
	}
	cout << endl << "Исходная матрица: " << endl;
	read_memory(memory, col, row);
	cout << endl;

	cout << "Новая матрица: " << endl;
	read_memory(new_memory, new_col, row);



	for (int i = 0; i < row; i++) {
		free(memory[i]);
	}
	free(zero_array);
	free(memory);
	free(new_memory);
}

void item2() {
	
	int* A = new int;
	int* B = new int;

	cout << endl << "Введите A: ";
	cin >> *A;
	cout << "Введите B: ";
	cin >> *B;
	
	
	*A *= 2;
	int* pTmp = new int(*B);
	*B = *A;
	*A = *pTmp;

	cout << "A: " << *A << endl;
	cout << "B: " << *B << endl;

	delete A;
	delete B;
	delete pTmp;
}


int main() {
	setlocale(LC_ALL, "Russian");

	item1();
	item2();
	
}