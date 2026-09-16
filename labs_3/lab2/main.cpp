#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

enum string_types {
	vow,
	cons,
	num,
	symb,
	size, // 4
	none
};

class arr {
private:
	int sizes[string_types::size] = {
		0, // гласные
		0, // согласные
		0, // цифры
		0 // другие символы
	};
	char** output;
	std::string input = "";


	bool is_vow(char x) {
		return x == -32 || x == -27 || x == -72 || x == -24 || x == -18 || x == -13 || x == -5 || (x >= -3 && x <= -1);
	}

	char lower_case(char x) {
		return (x == -88 ? -72 : (x >= -64 && x < -32) ? x + 32 : x);
	}

	void add_symbol(char symbol, string_types type) {
		if (type == string_types::none)
			return;

		for (int j = 0; j < sizes[type]; ++j) {
			if (lower_case(symbol) == output[type][j]) {
					return;
			}
		}
		sizes[type]++;
		output[type] = (char*)realloc(output[type], sizeof(char) * sizes[type]);
		output[type][sizes[type] - 1] = lower_case(symbol);
	}

	string_types get_type(char i) {
		if (i == 0)
			return string_types::none;

		if ((int)i >= 48 && (int)i <= 57) {
			return string_types::num;
		}
		if (((int)i >= -64 && (int)i <= -1) || (int)i == -88 || (int)i == -72) {
			switch (is_vow(lower_case(i))) {
			case true: {
				return string_types::vow;
			}
			case false: {
				return string_types::cons;
			}
			}
		}
		if (i == '@' || (i >= 65 && i <= 90) || (i >= 97 && i <= 122)) {
			return string_types::none;
		}
		return string_types::symb;
	}

	void remove_symbol(int i, int j) {
		sizes[i]--;
		for (int k = j; k < sizes[i]; ++k) {
			std::swap(output[i][k], output[i][k + 1]);
		}
		output[i] = (char*)realloc(output[i], sizeof(char) * sizes[i]);
	};
	void process_input(std::string& input_) {
		input = input_;
		input.resize(50);
		input.reserve(7);
		for (int j = 0; j <= input_.size(); j++) {
			char i = input[j];
			if (i == 0)
				break;
	
			auto type = get_type(i);
			if (type != string_types::none) {
				add_symbol(i, type);
			}
		}
		sort();
	}
	
	void console_color(char symbol) {
		for (int i = 0; i < string_types::size; ++i) {
			for (int j = 0; j < sizes[i]; ++j) {
				if (lower_case(symbol) == output[i][j]) {
					switch (i) {
					case 0: std::cout << "\033[31m"; return;
					case 1: std::cout << "\033[34m"; return;
					case 2: std::cout << "\033[32m"; return;
					case 3: std::cout << "\033[33m"; return;
					}
				}
			}
		}
		std::cout << "\033[0m";
		return;
	}

	void sort() {
		for (int i = 0; i < string_types::size; ++i) {
			for (int j = 0; j < sizes[i] - 1; ++j) {
				for (int k = j + 1; k < sizes[i]; ++k) {
					if (output[i][j] > output[i][k])
						std::swap(output[i][j], output[i][k]);
				}
			}
		}
	}
public:
	arr() {
		output = (char**)malloc(4 * sizeof(char*));
		for (char x = 0; x < 4; ++x) {
			output[x] = (char*)malloc(0 * sizeof(char));
		}
	}
	arr(std::string& input_) : arr() {
		process_input(input_);
	}
	void print() {
		for (int i = 0; i < string_types::size; ++i) {
			for (int j = 0; j < sizes[i]; ++j) {
				std::cout << output[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::string echo = input;
		bool added_extras = false;
		int index = 0;

		for (auto i : input) {
			if (i == 0) {
				if (added_extras)
					break;
				added_extras = true;
				for (auto q : "+123АБВ") {
					if (i == 0)
						i = q;
					input[index] = q;
					index++;
				}
			}
			console_color(lower_case(i));
			std::cout << i;
			index++;
		}
		std::cout << "\033[0m\n";
		input = echo;
		
	}

	~arr() {
		for (int i = 0; i < string_types::size; i++) {
			for (int j = 0; j < sizes[i]; ++j) {
			}
			free(output[i]);
		}
		free(output);
	}

	char* operator[](unsigned int index) {
		if (index >= string_types::size)
			exit(-1);

		return output[index];
	}

	void del(int i, int j) {
		if (i < string_types::size)
			if (j < sizes[i])
				remove_symbol(i, j);
	}

	void del(char x) {
		for (int i = 0; i < string_types::size; ++i) {
			for (int j = 0; j < sizes[i]; ++j) {
				if (lower_case(x) == output[i][j]) {
					remove_symbol(i, j);
				}
			}
		}
	}

	arr& operator++() {
		std::vector<std::string> buffers;
		buffers.reserve(4);
		for (int i = 0; i < string_types::size; ++i) {
			std::string buffer = "";
			for (int j = 0; j < sizes[i]; ++j) {
				if (output[i][j] == '9') {
					output[i][j] = '0';
				}
				else {
					auto first_t = get_type(output[i][j]);
					++output[i][j];
					if (first_t != get_type(output[i][j]))
						buffer += output[i][j];
				}
			}
			buffers.emplace_back(buffer);
		}
		sort();
		return *this;
	}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	char input[57] = "";
	std::cin.getline(input, 50);
	auto input_str = std::string(input);
	arr result = arr(input_str);
	result.print();
	++result;
	result.print();
}