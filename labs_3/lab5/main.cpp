#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

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

                if (de_mors.find(c) != de_mors.end()) {
                    result += de_mors.at(c);
                    if (!(count >= size)) {
                        result += "/";
                    }
                }
                else {
                    if (c == ' ') {
                        result += "/";
                        continue;
                    }
                    result += "?";
                }
            }
            result += "\n";
        }
        std::ofstream outfile("p1_output.txt");
        outfile << result;
    }
}

std::vector<std::string> trans(std::ifstream& file) {
    std::vector<std::string> out;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::string code = "";
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] != '/' ) {
                    code += line[i];
                    if (i == line.size() - 1) {
                        out.emplace_back(code);
                        break;
                    }
                }
                else {
                    out.emplace_back(code);
                    code = "";
                }
            }
        }
    }
    for (int j = 0; j < out.size(); ++j) {
        for (int i = 1; i < out[j].size(); ++i) {
            if (out[j][i] == '-' && rand() % 5 == 0) {
                out[j][i] = '*';
                break;
            }
        }
    }
    return out;
}
std::vector<std::string>* restore(std::vector<std::string>& code);

bool is_decodeable(std::vector<std::string>& code) {
    for (auto symbol : code) {
        if (mors.find(symbol) == mors.end()) {
            return false;
        }
    }
    return true;
}

std::string decode_write(std::vector<std::string>& code) {
    std::string string = "";
    for (auto symbol : code) {
        if (mors.find(symbol) != mors.end()) {
            string += mors[symbol];
        }
        else if (symbol.size() == 0) {
            string += " ";
        }
        else {
            string += "?";
        }
    }
    return string;
}

void decode(std::ifstream& file) {
    auto code = trans(file);
    std::string string = "";
    bool decodeable = is_decodeable(code);
    
    std::vector<std::string>* vars = nullptr;
    if (!decodeable) {
        std::cout << std::endl << "Неоднозначная расшифровка. Варианты:" << std::endl;
        vars = restore(code);
    }
    else {
        string = decode_write(code);
        std::cout << string << std::endl << std::endl
            << "0. Готово" << std::endl
            << "1. Варианты расшифровки" << std::endl;
        int input;
        std::cin >> input;
        if (input) {
            vars = restore(code);
        }
    }
    if (vars) {
        for (int i = 0; i < vars->size(); ++i) {
            std::cout << i + 1 << ". " << vars->at(i) << std::endl;
        }
        std::cout << "Вариант: ";
        unsigned int chosen = 0;
        while (!chosen || chosen > vars->size()) {
            std::cin >> chosen;
        }
        string = vars->at(chosen - 1);
    }
    std::ofstream outfile("p3_output.txt");
    outfile << string;
}

void restore_rec(std::vector<std::string>& code, int current_symbol, std::vector<std::string> current_var, std::vector<std::vector<std::string>>& all_code_vars);

std::vector<std::string>* restore(std::vector<std::string>& code) {
    auto return_vec = new std::vector<std::string>();
    std::vector<std::vector<std::string>> all_code_vars;
    restore_rec(code, 0, {}, all_code_vars);
    for (auto code : all_code_vars) {
        return_vec->emplace_back(decode_write(code));
    }
    return return_vec;
}

void restore_rec(std::vector<std::string>& code, int current_symbol, std::vector<std::string> current_var, std::vector<std::vector<std::string>>& all_code_vars) {
    if (current_symbol >= code.size()) {
        if (current_var.size() == code.size())
            all_code_vars.emplace_back(current_var);

        return;
    }

    if (mors.find(code[current_symbol]) != mors.end()) {
        auto next_var(current_var);
        next_var.emplace_back(code[current_symbol]);
        restore_rec(code, current_symbol + 1, next_var, all_code_vars);
    }
        for (int i = 1; i < code[current_symbol].size(); i++) {
            if (code[current_symbol][i] == '*') {
                auto new_symbol = code[current_symbol];
                new_symbol[i] = '-';
                if (mors.find(new_symbol) != mors.end()) {
                    auto next_var(current_var);
                    next_var.emplace_back(new_symbol);
                    restore_rec(code, current_symbol + 1, next_var, all_code_vars);
                }
            }
        }
}

int main()
{
    srand(time(0));
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

    for (auto pair : mors) {
        de_mors[pair.second] = pair.first;
    }

    while (true) {
        int input;
        std::cout << std::endl
            << "1. Кодирование" << std::endl
            << "2. Передача" << std::endl
            << "3. Декодирование" << std::endl
            << std::endl;
        std::cin >> input;
        switch (input) {
        case 1: {
            std::ifstream file;
            file.open("input.txt");
            code(file);
            break;
        }
        case 2: {
            std::ifstream file;
            file.open("p1_output.txt");
            auto out = trans(file);

            std::ofstream outfile("p2_output.txt");
            int count = 0;
            for (auto symbol : out) {
                outfile << symbol;
                if (count != out.size() - 1)
                    outfile << '/';
                count++;
            }
            break;
        }
        case 3: {
            std::ifstream file;
            file.open("p1_output.txt");
            decode(file);
            break;
        }
        default: break;
        }
    }
}
