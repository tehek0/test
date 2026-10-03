#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

char console_colors[4] = { 4, 9, 2, 6 };
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class arr : public std::vector<std::vector<std::string>> {
	char selected_color_id = 0;
public:
	arr() = default;
	arr(std::ifstream& file) : arr() {

		std::string line;
		while (std::getline(file, line)) {
			std::vector<std::string> p;
			p.push_back(line);
			this->push_back(p);
		}
	}

	void delete_elem(int i, int j) {
		if (i >= this->size())
			abort();

		if (j >= this->at(i).size())
			abort();

		auto x = this->at(i);
		x.erase(x.begin() + j);
		x.shrink_to_fit();
	};
	void delete_elem(const std::string& str) {
		int i = 0;

		for (auto elem : *this) {
			int j = 0;
			for (auto elem2 : elem) {
				if (elem2 == str) {
					delete_elem(i, j);
					return;
				}
				++j;
			}
			++i;
		}
	}
	void add_endline(int k, std::string item) {
		if (k >= this->size())
			abort();

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

	arr operator+(const arr& other) {
		auto out = *this;
		if (other.size() != out.size())
			return out;

		for (int i = 0; i < out.size(); ++i) {
			for (int j = 0; j < out[i].size() && j < other[i].size(); ++j) {
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

	arr operator++(int) {
		return this->operator++();
	}
};



int main(int argc, char** argv) {
	SetConsoleOutputCP(1251);
	// ANSI
	std::ifstream file("C:\\vs\\input2.txt");
	arr l = arr(file);
	l.add_endline(0, "512345");
	l.add_endline(0, "67890");
	l.print();
	auto l2 = l;
	l2.add_endline(1, "Доп линия");
	l2.print();
	arr l3 = l + l2;
	l3.print();
	l3++;
	l3.print();
	
}