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
    book(QString& author, QString& name, QString& code, QString& contents, QString& type, std::vector<QString>& genres);
    QString get_genre(size_t id);
    void write_to_file();
};

