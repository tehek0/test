#pragma once
#include <QApplication>
#include <vector>
#include <fstream>

class book{
private:
    QString _author;
    QString _name;
    QString _code;
    QString _contents;
    QString _type;
    std::vector<QString> _genres;
public:
    QString get_author();
    QString get_name();
    QString get_code();
    QString get_contents();
    QString get_type();
    QString get_genre(size_t id);
    void write_to_file();
};

