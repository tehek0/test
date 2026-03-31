#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include <fstream>
#include <QFileDialog>
#include <QRegularExpression>

#define MAG_CODE 0
#define VRAG_CODE 1

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    for (size_t i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
}

void MainWindow::on_load_pressed()
{
    ui->load_error->setText(" ");

    QString path = QFileDialog::getOpenFileName();
    if (path == "") {
        ui->load_error->setText("Директория не указана");
        return;
    } else if (!(path.endsWith(".txt"))) {
        ui->load_error->setText("Неподдерживаемый формат файла");
        return;
    }
    QRegularExpression rx_line("^\\d, [\\w ]+, \\w+, \\d+, \\d+,\\d+,\\d+,\\d+\\z", QRegularExpression::UseUnicodePropertiesOption);
    std::ifstream file(path.toStdString());
    std::string line;
    unsigned int counter = 0;
    std::vector<magician> stack_magicians;
    std::vector<enemy> stack_enemies;
    std::vector<char> order;
    while (std::getline(file, line)) {
        ++counter;
        QString process_string = QString::fromStdString(line);
        QRegularExpressionMatch match = rx_line.match(process_string);
        if (!(match.hasMatch())) {
            QString errormsg = "Некорректные данные в файле: строка ";
            QString line_num;
            line_num.setNum(counter);
            errormsg += line_num;
            ui->load_error->setText(errormsg);
            return;
        }
        unsigned int code;
        QString name_result;
        QString type_result;
        unsigned int value_result;
        unsigned int health_result;
        armor armor_result;
        char arg_num = 0;
        QString input = "";
        for (size_t i = 0; i < (unsigned int)process_string.size(); ++i) {
            if ((arg_num != 1) && (process_string[i] == " "))
                continue;
            if ((process_string[i] != ",")) {
                input += process_string[i];
                if (i != (process_string.size() - 1))
                    continue;
            }

            switch(arg_num) {
            case 0:
                code = input.toUInt();
                break;
            case 1:
                name_result = input;
                break;
            case 2:
                type_result = input;
                break;
            case 3:
                value_result = input.toUInt();
                break;
            case 4:
                health_result = input.toUInt();
                break;
            case 5:
                armor_result.helmet = input.toUInt();
                break;
            case 6:
                armor_result.chestplate = input.toUInt();
                break;
            case 7:
                armor_result.boots = input.toUInt();
                break;
            }
            ++arg_num;
            input = "";
        }
        switch(code) {
        case MAG_CODE: {
            magician mag_putstack(name_result, type_result, value_result, health_result, armor_result);
            order.reserve(counter);
            order.push_back(MAG_CODE);
            stack_magicians.reserve(stack_magicians.size() + 1);
            stack_magicians.push_back(mag_putstack);
            break;
        }
        case VRAG_CODE: {
            enemy vrag_putstack(name_result, type_result, value_result, health_result, armor_result);
            order.reserve(counter);
            order.push_back(VRAG_CODE);
            stack_enemies.reserve(stack_enemies.size() + 1);
            stack_enemies.push_back(vrag_putstack);
            break;
        }
        default: {
            ui->load_error->setText("Необрабатываемый код");
            return;
        }
        }
    }
    size_t counter_mags = 0;
    size_t counter_vrags = 0;
    for (size_t i = 0; i < counter; ++i) {
        switch(order[i]) {
        case MAG_CODE: {
            magician* mag = new magician;
            *mag = stack_magicians[counter_mags];
            entities.reserve(entities.size() + 1);
            entities.push_back(mag);
            ++counter_mags;
            break;
        }
        case VRAG_CODE: {
            enemy* vrag = new enemy;
            *vrag = stack_enemies[counter_vrags];
            entities.reserve(entities.size() + 1);
            entities.push_back(vrag);
            ++counter_vrags;
            break;
        }
        default: {
            ui->load_error->setText("Необрабатываемый код");
            return;
        }
        }
    }
    ui->list->clear();
    for (size_t i = 0; i < entities.size(); ++i) {
        ui->list->addItem(entities[i]->make_list_item());
    }
}



void MainWindow::on_list_itemDoubleClicked(QListWidgetItem *item)
{
    card* craft = new card(entities[ui->list->row(item)], this, ui, item);
    craft->show();
}

