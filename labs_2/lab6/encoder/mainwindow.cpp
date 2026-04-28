#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QFileDialog>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void add_object(QString name, QString desc, double coef, QString type) {
    json parser;
    std::ifstream input("output.json");
    if (input.is_open()) {
        try {
            parser = json::parse(input);
        } catch(...) {
            parser = json::array();
        }
    } else {
        parser = json::array();
    }

    json object = json::object();
    object["name"] = name.toStdString();
    object["desc"] = desc.toStdString();
    object["coef"] = coef;
    object["type"] = type.toStdString();

    parser.push_back(object);

    std::ofstream output("output.json");
    output.clear();
    output << parser.dump(2);
}

void add_object(json object) {
    json parser;
    std::ifstream input("output.json");
    if (input.is_open()) {
        try {
            parser = json::parse(input);
        } catch(...) {
            parser = json::array();
        }
    } else {
        parser = json::array();
    }

    parser.push_back(object);

    std::ofstream output("output.json");
    output.clear();
    output << parser.dump(2);
}

void MainWindow::on_add_to_json_clicked()
{
    bool had_exceptions = false;
    QString name_input = ui->name_line->text();
    if (name_input.size() == 0) {
        had_exceptions = true;
        ui->name_error->setText("* Обязательное поле");
    }
    QString desc_input = ui->desc_line->text();
    if (desc_input.size() == 0) {
        had_exceptions = true;
        ui->desc_error->setText("* Обязательное поле");
    }
    QString coef_input = ui->coef_line->text();
    if (coef_input.size() == 0) {
        had_exceptions = true;
        ui->coef_error->setText("* Обязательное поле");
    } else {
        QRegularExpression coef_float_reg_exp("^(\\d+)(.|,)(\\d+)$");
        QRegularExpression coef_int_reg_exp("^(\\d+)$");
        if ((!(coef_float_reg_exp.match(coef_input).hasMatch())) && (!(coef_int_reg_exp.match(coef_input).hasMatch()))) {
            had_exceptions = true;
            ui->coef_error->setText("* Неподходящий формат числа");
            ui->coef_line->setStyleSheet("color: rgb(255, 0, 0);");
        }
    }
    QString type_input = ui->type_line->text();
    if (type_input.size() == 0) {
        had_exceptions = true;
        ui->type_error->setText("* Обязательное поле");
    }

    if (had_exceptions == true)
        return;



    ui->txt_error->setText("");

    add_object(name_input, desc_input, coef_input.replace(",", ".").toDouble(), type_input);
}


void MainWindow::on_name_line_textEdited(const QString &arg1)
{
    ui->name_error->setText("");
    ui->txt_error->setText("");
}


void MainWindow::on_desc_line_textEdited(const QString &arg1)
{
    ui->desc_error->setText("");
    ui->txt_error->setText("");
}


void MainWindow::on_coef_line_textEdited(const QString &arg1)
{
    ui->coef_error->setText("");
    ui->coef_line->setStyleSheet("");
    ui->txt_error->setText("");
}


void MainWindow::on_type_line_textEdited(const QString &arg1)
{
    ui->type_error->setText("");
    ui->txt_error->setText("");
}


void MainWindow::on_txt_insert_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (!(path.endsWith(".txt"))) {
        ui->txt_error->setStyleSheet("color: rgb(255, 0, 0);");
        ui->txt_error->setText("* Неподходящий формат файла");
        return;
    }
    std::ifstream input(path.toStdString());
    std::string line;
    // unsigned int line_counter = 0;
    // std::vector<json> objects;
    QRegularExpression reg_exp("^[\\w, ]+/[\\w,.!? ]+/(((\\d+)(.|,)(\\d+))|(\\d+))/[\\w, ]$", QRegularExpression::UseUnicodePropertiesOption);
    // while (std::getline(input, line)) {
        // ++line_counter;
    std::getline(input, line);
    QString process_line = QString::fromStdString(line);
    if (!reg_exp.match(process_line).hasMatch()) {
        ui->txt_error->setStyleSheet("color: rgb(255, 0, 0);");
        ui->txt_error->setText(QString("* Ошибка входных данных"));
        return;
    }
    QString writer = "";
    QString name_input;
    QString desc_input;
        // double coef_input;
    QString coef_input;
    QString type_input;
    char arg_num = 0;
    for (unsigned int i = 0; i < process_line.size(); ++i) {
        if (process_line[i] != "/")
            writer += process_line[i];

        if (process_line[i] == "/" || (i == process_line.size() - 1)) {
            switch(arg_num) {
                case 0: {
                    name_input = writer;
                    ++arg_num;
                    writer = "";
                    break;
                }
                case 1: {
                    desc_input = writer;
                    ++arg_num;
                    writer = "";
                    break;
                }
                case 2: {
                    coef_input = writer;
                    ++arg_num;
                    writer = "";
                    break;
                }
                case 3: {
                    type_input = writer;
                    ++arg_num;
                    writer = "";
                    break;
                }
            }
        }
    }
    ui->name_line->setText(name_input);
    ui->desc_line->setText(desc_input);
    ui->coef_line->setText(coef_input);
    ui->type_line->setText(type_input);
        // json object = json::object();
        // object["name"] = name_input.toStdString();
        // object["desc"] = desc_input.toStdString();
        // object["coef"] = coef_input;
        // object["type"] = type_input.toStdString();
        // objects.reserve(objects.size() + 1);
        // objects.push_back(object);

    // for (unsigned int i = 0; i < objects.size(); ++i) {
    //     add_object(objects[i]);
    // }
    ui->txt_error->setStyleSheet("color: rgb(0, 205, 0);");
    ui->txt_error->setText(QString("* Данные загружены успешно!"));
}

