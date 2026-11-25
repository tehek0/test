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

std::vector<std::string> vector_symbol(std::ifstream& file) {
    std::vector<std::string> out;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::string code = "";
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] != '/') {
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
    return out;
}

std::vector<std::string> trans(std::ifstream& file) {
    std::vector<std::string> out = vector_symbol(file);
    
    for (int j = 0; j < out.size(); ++j) {
        for (int i = 1; i < out[j].size(); ++i) {
            if (out[j][i] == '-' && rand() % 5 == 0) {
                out[j][i] = '*';
                break;
            }
        }
    }
    file.close();
    return out;
}
std::vector<std::string>* restore(std::vector<std::string>& code);

bool is_decodeable(std::vector<std::string>& code) {
    for (auto symbol : code) {
        if (symbol.size() && (mors.find(symbol) == mors.end())) {
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
    auto code = vector_symbol(file);
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
        std::string correct_string;
        unsigned int correct_id = 0;
        std::ifstream input_file;
        input_file.open("input.txt");
        std::getline(input_file, correct_string);
        for (int i = 0; i < vars->size(); ++i) {
            std::cout << i + 1 << ". " << vars->at(i) << std::endl;
            if (vars->at(i) == correct_string)
                correct_id = i + 1;
        }
        std::cout << "Верный вариант: " << correct_id << std::endl;
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
    else if (code[current_symbol].size() == 0) {
        auto next_var(current_var);
        next_var.emplace_back("");
        restore_rec(code, current_symbol + 1, next_var, all_code_vars);
        return;
    }
    for (int i = 1; i < code[current_symbol].size(); i++) {
        if (code[current_symbol][i] == '*') {
            auto new_symbol = code[current_symbol];
            new_symbol[i] = '-';
            if (mors.find(code[current_symbol]) != mors.end()) {
                auto next_var(current_var);
                next_var.emplace_back(code[current_symbol]);
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
            << "4. Восстановление" << std::endl
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
            char in;
            std::cout << "Наложить на переданынй файл? y/n" << '\n';
            std::cin >> in;
            switch(in) {
            case 'y': {
                file.open("p2_output.txt");
                if (!file.is_open()) {
                    std::cout << "Файл ещё не был передан." << '\n';
                }
                break;
            }
            case 'n': {
                file.open("p1_output.txt");
                if (!file.is_open()) {
                    std::cout << "Файл не был закодирован." << '\n';
                }
                break;
            }
            }
            auto out = trans(file);
            file.close();

            std::ofstream outfile("p2_output.txt");
            outfile.flush();
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
            file.open("p2_output.txt");
            decode(file);
            break;
        }
        case 4: {
            std::ifstream file;
            file.open("p2_output.txt");
            std::string string = "";
            std::string correct_string;
            unsigned int correct_id = 0;
            std::ifstream input_file;
            input_file.open("input.txt");
            std::getline(input_file, correct_string);
            auto code = vector_symbol(file);
            auto restored = restore(code);
            if (restored) {

                for (int i = 0; i < restored->size(); ++i) {
                    std::cout << i + 1 << ". " << restored->at(i) << std::endl;
                    if (restored->at(i) == correct_string)
                        correct_id = i + 1;
                }
                std::cout << "Верный вариант: " << correct_id << std::endl;
                std::cout << "Вариант: ";
                unsigned int chosen = 0;
                while (!chosen || chosen > restored->size()) {
                    std::cin >> chosen;
                }
                string = restored->at(chosen - 1);
            }
            std::ofstream outfile("p3_output.txt");
            outfile << string;
            break;
        }
        default: break;
        }
    }
}
