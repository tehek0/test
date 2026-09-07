#include <iostream>
#include <string>

char is_opener_type(char x) {
	if (x == '(') {
		return 1;
	}
	if (x == '[') {
		return 2;
	}
	if (x == '{') {
		return 3;
	}
	return 0;
}

char is_closer_type(char x) {
	if (x == ')') {
		return 1;
	}
	if (x == ']') {
		return 2;
	}
	if (x == '}') {
		return 3;
	}
	return 0;
}

std::string input;
size_t size;
int find_closer(int pos, char type) {
	int seeker = pos;
	// std::cout << "Начало: " << seeker << "\n";
	int type_ = type;
	while (true) {
		seeker++;
		if (seeker >= size)
			return -1;
		char symbol = input[seeker];
		char symbol_type = is_closer_type(symbol);
		if (symbol_type != 0) {
			if (symbol_type != type_)
				return -1;
			// std::cout << "Конец: " << seeker << "\n";
			return seeker;
		}
		symbol_type = is_opener_type(symbol);
		if (symbol_type != 0) {
			int result = find_closer(seeker, symbol_type);
			if (result == -1)
				return -1;

			seeker = result;
		}
		else return -1;
	}
}

int main() {
	std::setlocale(LC_ALL, "Russian");

	std::cout << "Введите строку: ";
	std::cin >> input;
	size = input.size();
	int result = find_closer(0, is_opener_type(input[0]));
	while (result != size - 1) {
		if (result == -1)
			break;

		result = find_closer(result + 1, is_opener_type(input[result + 1]));
	}
	std::cout << (result == -1 ? "Строки не существует" : "Строка существует");
}