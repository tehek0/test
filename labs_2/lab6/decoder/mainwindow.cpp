#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../shared/inc.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFileDialog>

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

void add_object(json object, QString path) {
    json parser;
    std::ifstream input(path.toStdString());
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

    std::ofstream output(path.toStdString());
    output.clear();
    output << parser.dump(2);
}

void MainWindow::on_load_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (!(path.endsWith(".json"))) {
        ui->load_error->setStyleSheet("color: rgb(255, 0, 0);");
        ui->load_error->setText("* Неподходящий формат файла");
        return;
    }
    std::ifstream input(path.toStdString());
    json parser;
    try {
        parser = json::parse(input);
    } catch(...) {
        parser = json::array();
    }

    if (parser.size() == 0) {
        ui->load_error->setStyleSheet("color: rgb(255, 0, 0);");
        ui->load_error->setText("* Файл пуст");
        return;
    }

    ui->correct_items->clear();
    ui->incorrect_items->clear();

    std::ofstream correct("correct.json");
    std::ofstream incorrect("incorrect.json");

    if (correct.is_open()) {
        correct.clear();
        correct.close();
    }
    if (incorrect.is_open()) {
        incorrect.clear();
        incorrect.close();
    }
    std::vector<QTreeWidgetItem*> items;
    for (unsigned int i = 0; i < parser.size(); ++i) {
        QStringList list_for_item;
        json object = parser[i];

        bool is_incorrect = false;
        bool correct_markers[4] = {true, true, true, true};
        if (parser[i].contains("name")) {
            if (parser[i]["name"].is_string()) {
                list_for_item.append(QString::fromStdString(parser[i]["name"]));
                if (parser[i]["name"].get<std::string>().size() == 0) {
                    is_incorrect = true;
                    correct_markers[0] = false;
                }
            } else {
                json j = parser[i]["name"];
                if (j.is_array())
                    list_for_item.append(QString("[ ... ]"));
                if (j.is_object())
                    list_for_item.append(QString("{ ... }"));
                if (j.is_boolean())
                    list_for_item.append(QString("%1").arg((bool)j));
                if (j.is_number_float())
                    list_for_item.append(QString("%1").arg((double)j));
                if (j.is_number_integer())
                    list_for_item.append(QString("%1").arg((int)j));
                is_incorrect = true;
                correct_markers[0] = false;
            }
        } else {
            list_for_item.append(QString(""));
            is_incorrect = true;
            correct_markers[0] = false;
        }
        if (parser[i].contains("desc")) {
            if (parser[i]["desc"].is_string()) {
                list_for_item.append(QString::fromStdString(parser[i]["desc"]));
                if (parser[i]["desc"].get<std::string>().size() == 0) {
                    is_incorrect = true;
                    correct_markers[1] = false;
                }
            } else {
                json j = parser[i]["desc"];
                if (j.is_array())
                    list_for_item.append(QString("[ ... ]"));
                if (j.is_object())
                    list_for_item.append(QString("{ ... }"));
                if (j.is_boolean())
                    list_for_item.append(QString("%1").arg((bool)j));
                if (j.is_number_float())
                    list_for_item.append(QString("%1").arg((double)j));
                if (j.is_number_integer())
                    list_for_item.append(QString("%1").arg((int)j));
                is_incorrect = true;
                correct_markers[1] = false;
            }
        } else {
            list_for_item.append(QString(""));
            is_incorrect = true;
            correct_markers[1] = false;
        }
        if (parser[i].contains("coef")) {
            if (parser[i]["coef"].is_number_float() || parser[i]["coef"].is_number_integer()) {
                list_for_item.append(QString("%1").arg((double)parser[i]["coef"]));
                if (parser[i]["coef"] < 0 || parser[i]["coef"] > 1) {
                    is_incorrect = true;
                    correct_markers[2] = false;
                }
            } else {
                json j = parser[i]["coef"];
                if (j.is_array())
                    list_for_item.append(QString("[ ... ]"));
                if (j.is_object())
                    list_for_item.append(QString("{ ... }"));
                if (j.is_string())
                    list_for_item.append(QString::fromStdString(j));
                if (j.is_boolean())
                    list_for_item.append(QString("%1").arg((bool)j));
                is_incorrect = true;
                correct_markers[2] = false;
            }
        } else {
            list_for_item.append(QString(""));
            is_incorrect = true;
            correct_markers[2] = false;
        }
        if (parser[i].contains("type")) {
            if (parser[i]["type"].is_string()) {
                list_for_item.append(QString::fromStdString(parser[i]["type"]));
                if (parser[i]["type"].get<std::string>().size() == 0) {
                    is_incorrect = true;
                    correct_markers[3] = false;
                }
            } else {
                json j = parser[i]["type"];
                if (j.is_array())
                    list_for_item.append(QString("[ ... ]"));
                if (j.is_object())
                    list_for_item.append(QString("{ ... }"));
                if (j.is_boolean())
                    list_for_item.append(QString("%1").arg((bool)j));
                if (j.is_number_float())
                    list_for_item.append(QString("%1").arg((float)j));
                if (j.is_number_integer())
                    list_for_item.append(QString("%1").arg((int)j));
                is_incorrect = true;
                correct_markers[3] = false;
            }
        } else {
            list_for_item.append(QString(""));
            is_incorrect = true;
            correct_markers[3] = false;
        }
        qInfo() << i << list_for_item << is_incorrect;
        QTreeWidgetItem* item = new QTreeWidgetItem(list_for_item);
        if (is_incorrect == false) {
            items.reserve(items.size() + 1);
            items.emplace_back(item); // to sort
            add_object(object, QString("correct.json"));
        } else {
            for (char k = 0; k < 4; ++k) {
                if (correct_markers[k] == false)
                    item->setBackground(k, QBrush(Qt::red));
            }
            ui->incorrect_items->addTopLevelItem(item);
            add_object(object, QString("incorrect.json"));
        }
    }
    for (size_t i = 0; i < items.size(); ++i) {
        for (size_t j = i; j < items.size(); ++j) {
            if (items[i]->text(0) < items[j]->text(0)) {
                std::swap(items[i],items[j]);
            }
        }
    }
    for (size_t i = 0; i < items.size(); ++i) {
        ui->correct_items->addTopLevelItem(items[i]);
    }
    ui->load_error->setStyleSheet("color: rgb(0, 205, 0);");
    ui->load_error->setText("* Предметы добавлены");
}

