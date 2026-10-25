#pragma once
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <fstream>
#include <QPushButton>
#include <QPoint>


struct node {
    node* left = nullptr;
    node* right = nullptr;
    QString val;
    node(const QString& str) {
        val = str;
    }

};

class tree : public QWidget {

    Q_OBJECT

public:
    node* head;
    int levels = 0;

    tree() {
        std::string path = QFileDialog::getOpenFileUrl().path().toStdString().erase(0, 1);
        std::ifstream file(path);
        qInfo() << path;
        std::string line;
        QStringList read;
        while (std::getline(file, line)) {
            QString in = QString::fromStdString(line);
            read.append(in.split(" ", Qt::SkipEmptyParts));
            levels++;
        }

        std::vector<node*> buf;

        head = new node(read[0]);
        buf.push_back(head);

        int parent = 0;
        int string = 1;

        while (parent < buf.size() && string < read.size()) {
            node* current_parent = buf[parent];

            if (string < read.size()) {
                if (read[string] != "-") {
                    current_parent->left = new node(read[string]);
                    buf.push_back(current_parent->left);
                }
                string++;
            }

            if (string < read.size()) {
                if (read[string] != "-") {
                    current_parent->right = new node(read[string]);
                    buf.push_back(current_parent->right);
                }
                string++;
            }

            parent++;
        }
    }
    void draw() {
        QWidget* form = new QWidget();
        draw_recursive(head, form, QPoint(levels * 150, 30), 60 * levels);
        auto save = new QPushButton("Сохранить", form);
        form->show();
        form->connect(save, &QPushButton::clicked, this, &tree::save);
    }

public slots:
    void save() {
        std::ofstream file("out.txt");

        std::vector<node*> buf;
        buf.push_back(head);

        int current = 0;
        int current_level_nodes = 1;
        int next_level_nodes = 0;

        std::string current_line = "";

        while (current < buf.size()) {
            node* current_node = buf[current];
            current++;
            current_level_nodes--;

            if (current_node != nullptr) {
                current_line += current_node->val.toStdString() + " ";
                buf.push_back(current_node->left);
                buf.push_back(current_node->right);
                next_level_nodes += 2;
            } else {
                current_line += "- ";
            }

            if (current_level_nodes == 0) {
                bool has_real_nodes = false;
                for (size_t i = current; i < buf.size(); ++i) {
                    if (buf[i] != nullptr) {
                        has_real_nodes = true;
                        break;
                    }
                }

                if (!has_real_nodes) {
                    while (!current_line.empty() && (current_line.back() == ' ' || current_line.back() == '-')) {
                        if (current_line.back() == '-') {
                            current_line.pop_back();
                            if (!current_line.empty() && current_line.back() == ' ') current_line.pop_back();
                        } else {
                            current_line.pop_back();
                        }
                    }
                    if (!current_line.empty()) {
                        file << current_line;
                    }
                    break;
                }

                file << current_line << "\n";
                current_line = "";

                current_level_nodes = next_level_nodes;
                next_level_nodes = 0;
            }
        }
    }
private:
    void draw_recursive(node* current, QWidget* form, const QPoint& offset, int space) {
        if (!current) return;


        auto btn = new QPushButton(current->val, form);
        btn->show();
        btn->setGeometry(offset.x() - 25, offset.y(), 50, 50);
        draw_recursive(current->left, form, offset + QPoint(-space, 70), space / 2);
        draw_recursive(current->right, form, offset + QPoint(space, 70), space / 2);
    }
};
