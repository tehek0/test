// Вариант 2
#include <iostream>

using namespace std;

int counter = 0;
int* get_zeros(int** memory, int row, int col) {
	int* arr = static_cast<int*>(calloc(col * row, sizeof(int)));
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (memory[j][i] == 0) {
				arr[counter] = i;
				++counter;
			}
		}
	}
	return arr;

}

void print_memory(int** memory, int row, int col) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			cout << memory[j][i] << " ";
		}
		cout << endl;
	}
}

void item1() {
	const char base_col = 2;
	const char base_row = 2;
	int** memory = static_cast<int**>(calloc(base_col, sizeof(int*)));
	for (int i = 0; i < base_col; ++i) {
		memory[i] = static_cast<int*>(calloc(base_row, sizeof(int)));
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

	int col = (base_col + memory[1][0]);
	int row = (base_row + memory[0][0]);
	size_t col_size = col * sizeof(int*);
	size_t row_size = row * sizeof(int);
	int indexes = col * row;
	memory = static_cast<int**>(realloc(memory, col_size));
	for (int i = base_col; i < col; ++i) {
		memory[i] = static_cast<int*>(malloc(row_size));
	}
	memory[col - 1][row - 1] = memory[1][1];
	memory[col - 1][row - 2] = memory[1][0];
	memory[col - 2][row - 1] = memory[0][1];
	memory[col - 2][row - 2] = memory[0][0];
	

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if ((i >= row - 2) && (j == col - 2)) {
				break;
			}
			memory[j][i] = ((i * memory[col - 2][row - 1]) + (j * memory[col - 1][row - 1]));
			cerr << endl << ((i * memory[col - 2][row - 1]) + (j * memory[col - 1][row - 1]));
			
		}

	}

	cout << endl << "Исходная матрица: " << endl;
	print_memory(memory, row, col);
	cout << endl;

	int new_row = 0;
	int* zero_array = get_zeros(memory, row, col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			bool allow = 1;
			for (int k = 0; k < counter; ++k) {
				if (i == zero_array[k]) {
					allow = 0;
				}
			}
			if (allow != 1) {
				--new_row;
				break;
			}
			memory[j][new_row] = memory[j][i];
			
		}
		++new_row;
	}

	for (int i = row; i > new_row; --i) {
		for (int j = 0; j < col; ++j) {
			memory[j][i] = 0;
		}
	}
	
	

	cout << "Новая матрица: " << endl;
	print_memory(memory, new_row, col);

	
	for (int i = 0; i < col; ++i) {
		memory[i] = static_cast<int*>(realloc(memory[i], row_size));
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