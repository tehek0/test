#include <iostream>
#include <windows.h>
#include <string>

bool is_vow(char x) {
	return x == -64 || x == -59 || x == -88 || x == -56 || x == -50 || x == -45 || x == -37 || (x >= -35 && x <= -32) || x == -27 || x == -72 || x == -24 || x == -18 || x == -13 || x == -5 || (x >= -3 && x <= -1);
}

void add_symbol(char symbol, char str_id, char** output, int& size) {
	
	for (int j = 0; j < size; ++j) {
		if (symbol == output[str_id][j]) {
			return;
		}
	}
	size++;
	output[str_id] = (char*)realloc(output[str_id], sizeof(char) * size);
	output[str_id][size - 1] = symbol;
}

char console_color(char symbol, char** output, int* sizes) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < sizes[i]; ++j) {
			if (symbol == output[i][j]) {
				switch (i) {
				case 0: return 4;
				case 1: return 9;
				case 2: return 2;
				case 3: return 6;
				}
			}
		}
	}
	return 7;
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char input[50] = "";
	std::cin.getline(input, 50);
	
	int sizes[4] = {
		0, // гласные
		0, // согласные
		0, // цифры
		0 // другие символы
	};

	char** output = (char**)malloc(4 * sizeof(char*));
	for (char x = 0; x < 4; ++x) {
		output[x] = (char*)malloc(1 * sizeof(char));
		std::cout << (void*)output[x] << "\n";
	}
	for (auto i : input) {
		if (i == 0)
			break;

		if ((int)i >= 48 && (int)i <= 57) {
			add_symbol(i, 2, output, sizes[2]);
			continue;
		}
		if (((int)i >= -64 && (int)i <= -1) || (int)i == -88 || (int)i == -72) {
			switch (is_vow(i)) {
				case true: {
					add_symbol(i, 0, output, sizes[0]);
					continue;
				}
				case false: {
					add_symbol(i, 1, output, sizes[1]);
					continue;
				}
			}
		}
		if (i == (char)"@") {
			continue;
		}
		add_symbol(i, 3, output, sizes[3]);
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < sizes[i]; ++j) {
			std::cout << output[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (auto i : input) {
		if (i == 0)
			break;
		SetConsoleTextAttribute(hConsole, console_color(i, output, sizes));
		std::cout << i;
	}

	for (int i = 0; i < 4; i++) {
		free(output[i]);
	}
	free(output);

	SetConsoleTextAttribute(hConsole, 7);
}