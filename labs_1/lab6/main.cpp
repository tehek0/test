// Вариант 2
#include <iostream>

using namespace std;

int counter = 0;
int* get_zeros(int** memory, int row, int col) {
	int* arr = (int*)(calloc(col * row, sizeof(int)));
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (memory[i][j] == 0) {
				arr[counter] = i;
				++counter;
				break;
			}
		}
	}
	return arr;

}

void print_memory(int** memory, int row, int col) {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			cout << memory[i][j] << " ";
		}
		cout << endl;
	}
}


int main() {
	setlocale(LC_ALL, "Russian");

	const char base_col = 2;
	const char base_row = 2;
	int** memory = (int**)calloc(base_col, sizeof(int*));
	for (int i = 0; i < base_row; ++i) {
		memory[i] = (int*)calloc(base_row, sizeof(int));
		for (int j = 0; j < base_col; ++j) {
			int input;
			switch (i)
			{
			case 0:
			{
				switch (j) {
				case 0:
					cout << "Введите A строк для добавления вверх: "; break;
				case 1:
					cout << "Введите B строк для добавления влево: "; break;
				default:
					break;
				}
				do {
					cin >> input;
					if (input < 0)
						cout << "Введите корректное значение: ";
				} while (input < 0);
				break;
			}
			case 1:
			{
				switch (j) {
				case 0:
					cout << "Введите коэфициент C: "; break;
				case 1:
					cout << "Введите коэфициент Д: "; break;
				default:
					break;
				}
				cin >> input;
				break;
			}
			default:
				break;
			}
			memory[i][j] = input;
		}
	}

	int row = (base_row + memory[0][0]);
	int col = (base_col + memory[0][1]);
	
	int col_size = col * sizeof(int);
	int row_size = row * sizeof(int*);
	memory = (int**)(realloc(memory, row_size));
	for (int i = base_col; i < row; ++i) {
		memory[i] = (int*)(calloc(col, sizeof(int)));
	}
	for (int i = 0; i < row; ++i) {
		memory[i] = (int*)(realloc(memory[i], col_size));
	}
	
	
	memory[row - 2][col - 2] = memory[0][0]; // A
	memory[row - 2][col - 1] = memory[0][1]; // B
	memory[row - 1][col - 1] = memory[1][1]; // C
	memory[row - 1][col - 2] = memory[1][0]; // Д
	
	

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if ((i >= row - 2) && (j == col - 2)) {
				break;
			}
			memory[i][j] = ((i * memory[row - 1][col - 2]) + (j * memory[row - 1][col - 1]));
			

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
			memory[new_row][j] = memory[i][j];

		}
		++new_row;
	}
	
	

	for (int i = new_row; i < row; ++i) {
		free(memory[i]);
	}



	cout << "Новая матрица: " << endl;
	print_memory(memory, new_row, col);


	for (int i = 0; i < new_row; ++i) {
		free(memory[i]);
	}

	free(memory);
	free(zero_array);


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

	exit(0);
}