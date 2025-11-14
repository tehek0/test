// Вариант 2
#include <iostream>

using namespace std;

int counter = 0;
int* get_zeros(int** memory, int col, int row) {
	int* arr = static_cast<int*>(calloc(row * col, sizeof(int)));
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

void print_memory(int** memory, int col, int row) {
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
	int** memory = static_cast<int**>(calloc(base_row, sizeof(int*)));
	for (int i = 0; i < base_row; ++i) {
		memory[i] = static_cast<int*>(calloc(base_col, sizeof(int)));
	}

	cout << "Введите A строк для добавления вверх: ";
	do {
		cin >> memory[0][0];
		if (memory[0][0] < 0)
			cout << "Введите корректное значение: ";
	} while (memory[0][0] < 0);

	cout << "Введите B строк для добавления влево: ";
	do {
		cin >> memory[1][0];
		if (memory[1][0] < 0)
			cout << "Введите корректное значение: ";
	} while (memory[1][0] < 0);

	cout << "Введите коэфициент C: ";
	cin >> memory[0][1];

	cout << "Введите коэфициент Д: ";
	cin >> memory[1][1];

	int row = (base_row + memory[1][0]);
	int col = (base_col + memory[0][0]);
	size_t row_size = row * sizeof(int*);
	size_t col_size = col * sizeof(int);
	int indexes = row * col;
	memory = static_cast<int**>(realloc(memory, row_size));
	for (int i = base_row; i < row; ++i) {
		memory[i] = static_cast<int*>(malloc(col_size));
	}
	memory[row - 1][col - 1] = memory[1][1];
	memory[row - 1][col - 2] = memory[1][0];
	memory[row - 2][col - 1] = memory[0][1];
	memory[row - 2][col - 2] = memory[0][0];
	

	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			if ((i >= col - 2) && (j == row - 2)) {
				break;
			}
			memory[j][i] = ((i * memory[row - 2][col - 1]) + (j * memory[row - 1][col - 1]));
			cerr << endl << ((i * memory[row - 2][col - 1]) + (j * memory[row - 1][col - 1]));
			
		}

	}

	cout << endl << "Исходная матрица: " << endl;
	print_memory(memory, col, row);
	cout << endl;

	int new_col = 0;
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
			memory[j][new_col] = memory[j][i];
			
		}
		++new_col;
	}
	
	

	cout << "Новая матрица: " << endl;
	print_memory(memory, new_col, row);

	
	for (int i = 0; i < row; ++i) {
		memory[i] = static_cast<int*>(realloc(memory[i], col_size));
		free(memory[i]);
	}

	free(memory);
	free(zero_array);

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
	
	exit(0);
}