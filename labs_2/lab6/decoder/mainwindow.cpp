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
    std::ofstream output(path.toStdString(), std::ios::app);
    if (!output.is_open()) {
        qInfo() << "файл не открылся =(";
        return;
    }
    output << object.dump() << std::endl;
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
    std::vector<shield> shields;
    std::string line;
    while (std::getline(input, line)) {
        QStringList list_for_item;
        json object;
        try {
            object = json::parse(line);
        } catch (...) {
            qInfo() << "EXCEPTION:" << line << "NOT A JSON OBJECT";
            continue;
        }

        bool is_incorrect = false;
        bool correct_markers[4] = {true, true, true, true};
        if (object.contains("name")) {
            if (object["name"].is_string()) {
                list_for_item.append(QString::fromStdString(object["name"]));
                if (object["name"].get<std::string>().size() == 0) {
                    is_incorrect = true;
                    correct_markers[0] = false;
                }
            } else {
                json j = object["name"];
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
        if (object.contains("desc")) {
            if (object["desc"].is_string()) {
                list_for_item.append(QString::fromStdString(object["desc"]));
                if (object["desc"].get<std::string>().size() == 0) {
                    is_incorrect = true;
                    correct_markers[1] = false;
                }
            } else {
                json j = object["desc"];
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
        if (object.contains("coef")) {
            if (object["coef"].is_number_float() || object["coef"].is_number_integer()) {
                list_for_item.append(QString("%1").arg((double)object["coef"]));
                if (object["coef"] < 0 || object["coef"] > 1) {
                    is_incorrect = true;
                    correct_markers[2] = false;
                }
            } else {
                json j = object["coef"];
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
        if (object.contains("type")) {
            if (object["type"].is_string()) {
                list_for_item.append(QString::fromStdString(object["type"]));
                if (object["type"].get<std::string>().size() == 0) {
                    is_incorrect = true;
                    correct_markers[3] = false;
                }
            } else {
                json j = object["type"];
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

        if (is_incorrect == false) {
            shields.reserve(shields.size() + 1);
            shields.emplace_back(shield(object));
            add_object(object, QString("correct.json"));
        } else {
            QTreeWidgetItem* item = new QTreeWidgetItem(list_for_item);
            for (char k = 0; k < 4; ++k) {
                if (correct_markers[k] == false)
                    item->setBackground(k, QBrush(Qt::red));
            }
            ui->incorrect_items->addTopLevelItem(item);
            add_object(object, QString("incorrect.json"));
        }
    }
    for (size_t i = 0; i < shields.size(); ++i) {
        for (size_t j = i; j < shields.size(); ++j) {
            if (shields[i].name < shields[j].name) {
                std::swap(shields[i],shields[j]);
            }
        }
    }
    for (size_t i = 0; i < shields.size(); ++i) {
        QStringList list_correct_item;
        list_correct_item.append(shields[i].name);
        list_correct_item.append(shields[i].desc);
        list_correct_item.append(QString::number(shields[i].coef));
        list_correct_item.append(shields[i].type);
        QTreeWidgetItem* item = new QTreeWidgetItem(list_correct_item);
        ui->correct_items->addTopLevelItem(item);
    }
    ui->load_error->setStyleSheet("color: rgb(0, 205, 0);");
    ui->load_error->setText("* Предметы добавлены");
}

