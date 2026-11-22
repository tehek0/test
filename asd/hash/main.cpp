#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

long long hash(const std::string& str) {
    long long h = 0;
    for (int i = 0; i < str.size() && i < 5; ++i) {
        h *= 5;
        h += str[i];
    }
    return abs(h);
}

class hashtable : public std::vector<std::string> {
public:
    void add(const std::string& str) {
        auto h = hash(str);
        if (h >= this->size()) {
            this->resize(h + 1);
        }
        while (!this->at(h).empty() && this->at(h) != str) {
            h++;
            if (h >= this->size()) {
                this->resize(h + 1);
                break;
            }
        }
        this->at(h) = str;
    }
    std::string& find(const std::string& str) {
        auto h = hash(str);
        while (h < this->size() && this->at(h) != str) {
            h++;
        }
        if (h < this->size()) {
            return this->at(h);
        }
        else { 
            abort(); 
        }
    }
};

struct chain {
    std::string val;
    chain* next = nullptr;
    chain(const std::string& str) {
        val = str;
    }
};

class hashtable_chained : public std::vector<chain*> {
public:
    void add(const std::string& str) {
        auto h = hash(str);
        if (h >= this->size()) {
            this->resize(h + 1);
        }
        chain* select = nullptr;
        if (this->at(h) != nullptr) {
            chain* select_prev = nullptr;
            select = this->at(h);
            while (select != nullptr && select->val != str) {
                select_prev = select;
                select = select->next;
            }
            if (select == nullptr) {
                select_prev->next = new chain(str);
            }
            return;
        }
        else {
            select = new chain(str);
        }
        this->at(h) = select;
    }
    std::string& find(const std::string& str) {
        auto h = hash(str);
        if (h < this->size()) {
            chain* selected = this->at(h);
            while (selected && selected->val != str) {
                selected = selected->next;
            }
            if (!selected)
                abort();

            return selected->val;
        }
        else {
            abort();
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    hashtable table;
    hashtable_chained chained_table;

    std::ifstream file;
    file.open("input.txt");

    if (!file.is_open())
        return -1;

    std::string line;
    std::string word;
    while (std::getline(file, line)) {
        word = "";
        for (int i = 0; i <= line.size(); ++i) {
            if (i < line.size() && line[i] != ' ') {
                word += line[i];
            }
            else {
                table.add(word);
                chained_table.add(word);
                word = "";
            }
        }
    }
    chained_table.find("пункта") = "не пункт.";
    std::ofstream out("out.txt");
    std::ofstream out_chained("out-chained.txt");
    for (long long i = 0; i < table.size(); ++i) {
        if (table.at(i).empty())
            continue;
        out << i << ": " << table.at(i) << '\n';
    }
    for (long long i = 0; i < chained_table.size(); ++i) {
        if (chained_table.at(i) == nullptr)
            continue;
        out_chained << i << ": ";
        chain* selected = chained_table.at(i);
        while (selected) {
            out_chained << selected->val;
            selected = selected->next;
            if (selected) {
                out_chained << " -> ";
            }
        }
        out_chained << '\n';
    }
}
