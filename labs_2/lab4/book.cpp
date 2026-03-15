#include "book.h"
#include <string>

book::book(QString& author, QString& name, QString& code, QString& contents, QString& type, std::vector<QString>& genres) {
    _author = author;
    _name = name;
    _code = code;
    _contents = contents;
    _type = type;
    _genres = genres;
}

void book::write_to_file() {
    std::ofstream result("result.txt");
    result << "Автор: " << _author.toStdString() << "\n"
           << "Название: " << _name.toStdString() << "\n"
           << "Код: " << _code.toStdString() << "\n"
           << "Наполнение: " << _contents.toStdString() << "\n"
           << "Тип издания: " << _type.toStdString() << "\n"
           << "Жанры: ";
    size_t genres_size = _genres.size();
    if (genres_size == 0) {
        result << "-";
        return;
    }
    for (size_t i = 0; i < genres_size; ++i) {
        result << _genres[i].toStdString() << (i == genres_size - 1 ? "" : ", ");
    }

}
