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
		char color = 0;
		for (auto elem : *this) {
			std::cout << '\n';
			for (auto elem2 : elem) {
				
				SetConsoleTextAttribute(hConsole, color[()]);
				std::cout << ' ';
				for (int i = 0; i < elem2.size(); ++i) {
					std::cout << elem2[i];
				}
			}
		}
	}
	void sort() {
		for (int i = 0; i < this->size(); ++i) {
			auto elem = this->at(i);
			for (auto elem2 : elem) {
				for (int i = 0; i < elem2.size() - 1; ++i) {
					for (int j = i + 1; j < elem2.size(); ++j) {
						if (elem2[i] > elem2[j]) {
								auto temp = elem2[i];
								elem2[i] = elem2[j];
								elem2[j] = temp;
						}
					}
				}
			}
			this->at(i) = elem;
		}
	}

};



int main(int argc, char** argv) {
	
	SetConsoleOutputCP(1251);
	std::ifstream file("C:\\vs\\input2.txt");
	arr l = arr(file);
	l.add_endline(0, "12345");
	l.add_endline(0, "67890");
	l.print();
}