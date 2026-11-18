#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <Windows.h>
#include <filesystem>

std::map<std::string, char> mors;
std::map<char, std::string> de_mors;

void code(std::ifstream& file) {
    if (file.is_open()) {
        std::string line;
        std::string result;
        while (getline(file, line)) {
            size_t size = line.size();
            size_t count = 0;
            for (auto c : line) {
                count++;
                
                try {
                    std::cout << c;
                    result += de_mors.at(c);
                    std::cout << result << '\n';
                    if (!(count >= size)) {
                        result += "/";
                    }
                } catch (std::exception& ex) {
                    result += "?";
                }
            }
            result += "\n";
        }
        std::ofstream outfile("out.txt");
        outfile << result;
    }
}


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    mors["*-"] = 'А';
    mors["-***"] = 'Б';
    mors["*--"] = 'В';
    mors["--*"] = 'Г';
    mors["-**"] = 'Д';
    mors["*"] = 'Е';
    mors["***-"] = 'Ж';
    mors["--**"] = 'З';
    mors["**"] = 'И';
    mors["*---"] = 'Й';
    mors["-*-"] = 'К';
    mors["*-**"] = 'Л';
    mors["--"] = 'М';
    mors["-*"] = 'Н';
    mors["---"] = 'О';
    mors["*--*"] = 'П';
    mors["*-*"] = 'Р';
    mors["***"] = 'С';
    mors["-"] = 'Т';
    mors["**-"] = 'У';
    mors["**-*"] = 'Ф';
    mors["****"] = 'Х';
    mors["-*-*"] = 'Ц';
    mors["---*"] = 'Ч';
    mors["----"] = 'Ш';
    mors["--*-"] = 'Щ';
    mors["*--*-*"] = 'Ъ';
    mors["-*--"] = 'Ы';
    mors["-**-"] = 'Ь';
    mors["**-**"] = 'Э';
    mors["**--"] = 'Ю';
    mors["*-*-"] = 'Я';
    mors[" "] = ' ';
    
    for (auto pair : mors) {
        de_mors[pair.second] = pair.first;
    }

    while (true) {
        int input;
        std::cout << std::endl
            << "1. Кодирование" << std::endl
            << "2. Передача" << std::endl
            << "3. Декодирование" << std::endl
            << "4. Восстановление" << std::endl
            << std::endl;
        std::cin >> input;
        switch (input) {
        case 1: {
            std::ifstream file;
            file.open("C:/in/input.txt");
            code(file);
            break;
        }
        default: break;
        }
    }
}
