#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

char console_colors[4] = { 4, 9, 2, 6 };
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class subarr : public std::vector<std::string> {
public:
	subarr() = default;
	std::string& operator[](int i) {
		if (this->size() <= i) {
			this->resize(i + 1);
		}
		return this->at(i);
	}
};

class arr : public std::vector<subarr> {
	char selected_color_id = 0;
public:
	arr() = default;
	arr(std::ifstream& file) : arr() {

		std::string line;
		while (std::getline(file, line)) {
			subarr p;
			p.push_back(line);
			this->push_back(p);
		}
	}

	void delete_elem(int i, int j) {
		if (i >= this->size())
			abort();

		if (j >= this->at(i).size())
			abort();

		this->at(i).erase(this->at(i).begin() + j);
		this->at(i).shrink_to_fit();

		if (this->at(i).size() == 0) {
			for (int k = i; k >= 0 && this->at(k).size() == 0; --k) {
				this->erase(this->begin() + k);
			}
		}
	};
	void delete_elem(const std::string& str) {
		int i = 0;

		for (int i = this->size() - 1; i >= 0; --i) {
			if (i >= this->size())
				i = this->size() - 1;
			for (int j = this->at(i).size() - 1; j >= 0; --j) {
				if (this->at(i).at(j) == str) {
					delete_elem(i, j);
				}
			}
		}
	}
	void add_endline(int k, std::string item) {
		if (k >= this->size()) {
			this->resize(k + 1);
		}

		this->at(k).push_back(item);
	}
	void print() {
		char color_i = 0;
		for (auto elem : *this) {
			std::cout << std::endl;
			SetConsoleTextAttribute(hConsole, console_colors[color_i]);
			(color_i > 3 ? color_i = 0 : color_i += 1);
			for (auto elem2 : elem) {


				std::cout << ' ';
				for (int i = 0; i < elem2.size(); ++i) {
					std::cout << elem2[i];
				}
			}
		}
		SetConsoleTextAttribute(hConsole, 7);
	}

	void sort_string(std::string& str) {
		for (int c1 = 0; c1 < str.size() - 1; ++c1) {
			for (int c2 = c1 + 1; c2 < str.size(); ++c2) {
				if (str[c1] > str[c2]) {
					auto temp = str[c1];
					str[c1] = str[c2];
					str[c2] = temp;
				}
			}
		}
	}

	void sort() {
		for (int i = 0; i < this->size(); ++i) {
			for (int j = 0; j < this->at(i).size(); ++j) {
				this->sort_string(this->at(i).at(j));
			}
		}

	}

	arr operator+(arr& other) {
		auto out = *this;

		for (int i = 0; i < out.size(); ++i) {
			auto min_size = min(other[i].size(), out[i].size());
			for (int j = 0; j < min_size; ++j) {
				out[i][j] += other[i][j];
			}
		}
		return out;
	}

	arr& operator++() {
		for (int i = 0; i < this->size(); ++i) {
			for (int j = 0; j < this->at(i).size(); ++j) {
				if (this->at(i)[j].size() != 0) {
					char ch = this->at(i)[j][0];
					if ((ch >= 'А' && ch <= 'Я') || (ch >= 'а' && ch <= 'я') || ch == 'Ё' || ch == 'ё') {
						++this->at(i)[j][0];
					}
				}
			}

		}
		return *this;
	}

	subarr& operator[](int i) {
		if (this->size() <= i) {
			this->resize(i + 1);
			this->at(i) = subarr();
		}
		return this->at(i);
	}

	arr operator++(int) {
		return this->operator++();
	}
};



int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	// ANSI
	std::ifstream file("C:\\vs\\input2.txt");
	arr l = arr(file);
	arr k;
	k[15][2] = "sasda";
	std::cout << k[15][2];
	l.sort();
	l.print();
	while (true) {

		std::cout << '\n' << "Индекс строки: ";
		int x;
		std::cin >> x;
		if (x < 0) {
			x = l.size() + x;
		}
		int action;
		std::cout << "Действие: " << '\n' << '\n' << "1. Добавить элемент в конец" << '\n' << "2. Отсортировать строку" << '\n' << "3. Удалить элемент" << '\n';
		std::cin >> action;
		switch (action) {
		case 1: {
			std::cout << "Строка: ";
			std::string item;
			std::cin >> item;
			l.add_endline(x, item);
			l.print();
			break;
		}
		case 2: {
			for (auto str : l[x]) {
				l.sort_string(str);
			}
			l.print();
			break;
		}
		case 3: {
			int action2;
			std::cout << "Действие: " << '\n' << '\n' << "1. Удалить по индексу" << '\n' << "2. Удалить по значению" << '\n';
			std::cin >> action2;
			switch (action2) {
			case 1: {
				int index;
				std::cout << "Индекс: ";
				std::cin >> index;
				if (x >= l.size()) {
					std::cout << "Пусто";
					continue;
				}
				if (index < 0 || index >= l[x].size()) {
					std::cout << "Некорректный индекс";
					continue;
				}
				l.delete_elem(x, index);
				l.print();
				break;
			}
			case 2: {
				std::cout << "Строка: ";
				std::string item;
				std::cin >> item;
				l.delete_elem(item);
				l.print();
				break;
			}
			default: {
				std::cout << "Некорректный ввод";
				continue;
			}
			}
			break;
		}
		default: {
			std::cout << "Некорректный ввод";
			continue;
		}
		}

	}
}