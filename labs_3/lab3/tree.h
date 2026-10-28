#pragma once
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <fstream>
#include <QPushButton>
#include <QPoint>
#include <QLabel>


struct node {
    node* left = nullptr;
    node* right = nullptr;
    QString val;
    node(const QString& str) {
        val = str;
    }

};

class tree : public QObject {

    Q_OBJECT

public:
    node* head;

    tree() {
        std::string path = QFileDialog::getOpenFileUrl().path().toStdString().erase(0, 1);
        std::ifstream file(path);
        qInfo() << path;
        std::string line;
        QStringList read;
        while (std::getline(file, line)) {
            QString in = QString::fromStdString(line);
            read.append(in.split(" ", Qt::SkipEmptyParts));
        }

        std::vector<node*> buf;

        head = new node(read[0]);
        buf.push_back(head);

        int parent = 0;
        int string = 1;

        while (parent < buf.size() && string < read.size()) {
            node* current_parent = buf[parent];

            if (string < read.size()) {
                if (read[string] != "-" && current_parent) {
                    current_parent->left = new node(read[string]);
                    buf.push_back(current_parent->left);
                } else {
                    buf.push_back(nullptr);
                }
                string++;
            }

            if (string < read.size()) {
                if (read[string] != "-" && current_parent) {
                    current_parent->right = new node(read[string]);
                    buf.push_back(current_parent->right);
                } else {
                    buf.push_back(nullptr);
                }
                string++;
            }

            parent++;
        }
    }
    void draw() {
        QWidget* form = new QWidget();
        draw_recursive(head, form, QPoint(5 * 150, 30), 60 * 5);
        auto save = new QPushButton("Сохранить", form);
        auto new_b = new QPushButton("Открыть новое", form);
        new_b->move(0, 100);
        auto length = new QLabel(form);
        length->setText(QString("Длина: ") + QString::number(len(head)));
        length->move(0, 200);

        form->show();
        form->connect(save, &QPushButton::clicked, this, &tree::save);
        form->connect(new_b, &QPushButton::clicked, [=] { tree* y = new tree(); y->draw();});
    }
    int len(node* current_node, int current = 1) {
        if (!current_node)
            return current - 1;

        int l = len(current_node->left, current + 1);
        int r = len(current_node->right, current + 1);
        return (l > r ? l : r);
    }

public slots:
    void save() {
        std::ofstream file("out.txt");

        QString line;
        save_recursive(head, line);

        file << line.toStdString();
    }
private:
    void draw_recursive(node* current, QWidget* form, const QPoint& offset, int space) {
        if (!current) return;

        auto write_to = current;
        auto btn = new QPushButton(current->val, form);
        btn->connect(btn, &QPushButton::clicked, [=] {auto new_text = QString::number(write_to->val.toInt() + 1); write_to->val = new_text; btn->setText(new_text);});
        btn->show();
        btn->setGeometry(offset.x() - 25, offset.y(), 50, 50);
        draw_recursive(current->left, form, offset + QPoint(-space, 70), space / 2);
        draw_recursive(current->right, form, offset + QPoint(space, 70), space / 2);
    }

    void save_recursive(node* current, QString& line) {
        if (!current) {
            return;
        }
        line = line + (current == head? "" : " ") + current->val;
        save_recursive(current->left, line);
        save_recursive(current->right, line);
    }
};
