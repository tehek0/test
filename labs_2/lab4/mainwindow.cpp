#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include "book.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegularExpression author_rx("[А-Я][а-я]{0,} [А-Я]{1,2}");
    QValidator *author_validator = new QRegularExpressionValidator(author_rx, this);
    ui->author->setValidator(author_validator);

    QRegularExpression name_rx("\"[а-я А-Я?,.()*\"-+=0-9]{0,}\"");
    QValidator *name_validator = new QRegularExpressionValidator(name_rx, this);
    ui->name->setValidator(name_validator);

    QRegularExpression code_rx("[0-9]{1,3}-[0-9]{1,5}");
    QValidator *code_validator = new QRegularExpressionValidator(code_rx, this);
    ui->code->setValidator(code_validator);

    QRegularExpression contents_rx("[1-9][0-9]{0,}/[1-9][0-9]{0,}");
    QValidator *contents_validator = new QRegularExpressionValidator(contents_rx, this);
    ui->contents->setValidator(contents_validator);
}

MainWindow::~MainWindow()
{
    delete ui->author->validator();
    delete ui->name->validator();
    delete ui->code->validator();
    delete ui->contents->validator();
    delete ui;
}







void MainWindow::on_author_textEdited()
{
    if (ui->author_error->text() == " ")
        return;
    ui->author_error->setText(" ");
}

void MainWindow::on_name_textEdited()
{
    if (ui->name_error->text() == " ")
        return;
    ui->name_error->setText(" ");
}

void MainWindow::on_code_textEdited()
{
    if (ui->code_error->text() == " ")
        return;
    ui->code_error->setText(" ");
}

void MainWindow::on_contents_textEdited()
{
    if (ui->contents_error->text() == " ")
        return;
    ui->contents_error->setText(" ");
}

void MainWindow::on_type_paper_clicked()
{
    if (ui->type_error->text() == " ")
        return;
    ui->type_error->setText(" ");
}

void MainWindow::on_type_digital_clicked()
{
    if (ui->type_error->text() == " ")
        return;
    ui->type_error->setText(" ");
}

void MainWindow::on_discard_pressed()
{
    ui->author->clear();
    ui->author_error->setText(" ");
    ui->name->clear();
    ui->name_error->setText(" ");
    ui->code->clear();
    ui->code_error->setText(" ");
    ui->contents->clear();
    ui->contents_error->setText(" ");
    ui->type_paper->setAutoExclusive(false);
    ui->type_paper->setChecked(false);
    ui->type_paper->setAutoExclusive(true);
    ui->type_digital->setAutoExclusive(false);
    ui->type_digital->setChecked(false);
    ui->type_digital->setAutoExclusive(true);
    ui->type_error->setText(" ");
    ui->genre_detective->setChecked(false);
    ui->genre_fiction->setChecked(false);
    ui->genre_novel->setChecked(false);


}

void MainWindow::on_save_pressed()
{
    bool had_errors = false;

    QString checker = ui->author->text();
    size_t checker_length = checker.length();

    if (checker.length() == 0) {
        ui->author_error->setText("*Обязательно поле");
        had_errors = true;
    } else {
        bool found_separation = false;
        for (size_t i = checker_length - 1; i > 0; --i) {
            if (checker[i] == " ") {
                if (i == checker_length - 1) {
                    break;
                }
                found_separation = true;
                break;
            }
        }
        if (found_separation == false) {
            ui->author_error->setText("*Не найдено ИО/И");
            had_errors = true;
        }
    }


    checker = ui->name->text();
    checker_length = checker.length();

    if (checker.length() == 0) {
        ui->name_error->setText("*Обязательно поле");
        had_errors = true;
    } else {
        if (checker[checker_length - 1] != "\"" && checker_length != 1) {
            ui->name_error->setText("*Кавычки не закрыты");
            had_errors = true;
        }
        if (checker_length == 1 || (checker_length == 2 && checker[1] == "\"")) {
            ui->name_error->setText("*Нет названия");
            had_errors = true;
        }
    }

    checker = ui->code->text();
    checker_length = checker.length();

    if (checker.length() == 0) {
        ui->code_error->setText("*Обязательно поле");
        had_errors = true;
    } else {
        bool found_separation = false;
        for (size_t i = checker_length - 1; i > 0; --i) {
            if (checker[i] == "-") {
                if (i == checker_length - 1) {
                    ui->code_error->setText("*Не найдена вторая часть");
                    had_errors = true;
                }
                found_separation = true;
                break;
            }
        }
        if (found_separation == false) {
            ui->code_error->setText("*Не найдено разделение: -");
            had_errors = true;
        }
    }

    checker = ui->contents->text();
    checker_length = checker.length();

    if (checker.length() == 0) {
        ui->contents_error->setText("*Обязательно поле");
        had_errors = true;
    } else {
        QString first_num = "";
        QString second_num = "";
        bool has_second_num = true;
        long long found_separation = -1;
        for (size_t i = 0; i < checker_length; ++i) {
            if (checker[i] == "/") {
                if (i == checker_length - 1) {
                    ui->contents_error->setText("*Не найдено второе число");
                    has_second_num = false;
                    had_errors = true;
                }
                found_separation = i;
                break;
            } else {
                first_num += checker[i];
            }
        }
        if (found_separation == -1) {
            ui->contents_error->setText("*Не найдено разделение: /");
            had_errors = true;
        } else {
            if (has_second_num == true) {
                for (size_t i = found_separation + 1; i < checker_length; ++i) {
                    second_num += checker[i];
                }
                if (first_num.toInt() < second_num.toInt()) {
                    ui->contents_error->setText("*Второе число больше первого");
                    had_errors = true;
                }
            }
        }
    }


    if (!ui->type_digital->isChecked() && !ui->type_paper->isChecked()) {
        ui->type_error->setText("*Обязательно поле");
        had_errors = true;
    }


    if (had_errors == true)
        return;




    QString type_result;
    std::vector<QString> genres_result;


    if (!ui->type_digital->isChecked() == true) {
        type_result = "Бумажное";
    } else {
        type_result = "Электронное";
    }

    if (ui->genre_detective->isChecked() == true) {
        genres_result.reserve(genres_result.size() + 1);
        genres_result.push_back("Детектив");
    }
    if (ui->genre_fiction->isChecked() == true) {
        genres_result.reserve(genres_result.size() + 1);
        genres_result.push_back("Фантастика");
    }
    if (ui->genre_novel->isChecked() == true) {
        genres_result.reserve(genres_result.size() + 1);
        genres_result.push_back("Роман");
    }


    QString author_result = ui->author->text();
    QString name_result = ui->name->text();
    QString code_result = ui->code->text();
    QString contents_result = ui->contents->text();

    book result(author_result, name_result, code_result, contents_result, type_result, genres_result);
    result.write_to_file();
}

