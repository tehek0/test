#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QLine>
#include <QLabel>
#include <QPen>
#include <QRect>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QRandomGenerator>
#include <fstream>
#include <map>
#include <ctime>

QRandomGenerator rng;

struct node {
    QString name;
    node(const QString& _name): name(_name) {}
};

struct vertex {
    node* n1 = nullptr;
    node* n2 = nullptr;
    float length;
    float coef;
    vertex(node* b, node* d, float l): n1(b), n2(d), length(l), coef((double)(rng.generate() % 40 / 10.0f) + 0.2f) {}
};

std::map<QString, node*> node_map;

class line_holder : public QObject {
public:
    QGraphicsLineItem* line;
    line_holder(QGraphicsLineItem* l, QObject* parent = nullptr) : QObject(parent) {
        line = l;
    }

};

class graph {
public:
    std::vector<vertex*> verteces;
    graph() = default;
    void reroll_coefs(QGraphicsView* gview) {
        for (auto v : verteces) {
            v->coef = (rng.generate() % 35 / 10.0f) + 0.2f;
            QPen pen;
            if (v->coef < 1.2) {
                pen = QPen(QColorConstants::Svg::lightgreen);
            } else if (v->coef < 1.9) {
                pen = QPen(QColorConstants::Svg::orange);
            } else if (v->coef < 3.3) {
                pen = QPen(QColorConstants::Svg::red);
            } else {
                pen = QPen(QColorConstants::Svg::mediumpurple);
            }
            pen.setWidth(4);
            static_cast<line_holder*>(gview->findChild<QObject*>(("vertex_line_" + v->n1->name + v->n2->name)))->line->setPen(pen);
            gview->findChild<QLabel*>(("vertex_disp_" + v->n1->name + v->n2->name))->setText(v->n1->name + v->n2->name + ": " + QString::number(v->length) + "(" + QString::number(v->length * v->coef) + ")");
        }
    }
    std::vector<vertex*> find_path(const QString& beginning, const QString& destination) {
        std::vector<std::vector<vertex*>> paths;
        for (auto vert : verteces) {
            if (vert->n1->name == beginning || vert->n2->name == beginning) {
                auto path = std::vector<vertex*>();
                path.emplace_back(vert);
                if (vert->n1->name == destination || vert->n2->name == destination) {
                    paths.emplace_back(path);
                    continue;
                }
                node* new_beginning = (vert->n1->name == beginning ? vert->n2 : vert->n1);
                path_out(new_beginning, path, destination, paths);
            }
        }
        std::vector<vertex*> chosen_path;
        double min_len = 1e+308;
        for (auto path : paths) {
            if (path.size() == 0)
                continue;
            double length = 0;
            for (auto vert : path) {
                length += (vert->coef * vert->length);
                if (length >= min_len)
                    break;
            }
            if (length < min_len) {
                chosen_path = path;
                min_len = length;
            }
        }
        return chosen_path;
    }
private:
    void path_out(node* beginning, std::vector<vertex*>& build_path, const QString& dest_name, std::vector<std::vector<vertex*>>& paths) {
        for (auto vert : verteces) {
            if (vert->n1 == beginning || vert->n2 == beginning) {
                bool visited = false;
                for (auto elem : build_path) {
                    if (elem == vert) {
                        visited = true;
                        break;
                    }
                }
                if (visited)
                    continue;
                auto path = std::vector<vertex*>(build_path);
                path.emplace_back(vert);
                if (vert->n1->name == dest_name || vert->n2->name == dest_name) {
                    paths.emplace_back(path);
                    continue;
                }
                node* new_beginning = (vert->n1 == beginning ? vert->n2 : vert->n1);

                path_out(new_beginning, path, dest_name, paths);
            }
        }
    }
};

class button_elipse_holder : public QPushButton {

public:
    QGraphicsEllipseItem* ellipse = nullptr;
    button_elipse_holder(const QString& text, QWidget* parent) : QPushButton(text, parent) {}
};

class mainwindow : public QWidget {
public:
    mainwindow(QWidget* parent = nullptr) : QWidget(parent) {}
    node* s_p1 = nullptr;
    node* s_p2 = nullptr;
    std::vector<vertex*> saved_path;
    void reset(bool recolor = true) {
        s_p1 = nullptr;
        s_p2 = nullptr;
        this->findChild<QLabel*>("begin_label")->setText("Начало: ");
        this->findChild<QLabel*>("end_label")->setText("Конец: ");
        this->findChild<QLineEdit*>("output")->setText("");
        this->findChild<QPushButton*>("save_button")->setDisabled(true);
        if (recolor) {
            for (auto vert : saved_path) {
                QPen pen;
                if (vert->coef < 1.2) {
                    pen = QPen(QColorConstants::Svg::lightgreen);
                } else if (vert->coef < 1.9) {
                    pen = QPen(QColorConstants::Svg::orange);
                } else if (vert->coef < 3.3) {
                    pen = QPen(QColorConstants::Svg::red);
                } else {
                    pen = QPen(QColorConstants::Svg::mediumpurple);
                }
                pen.setWidth(4);
                static_cast<line_holder*>(this->findChild<QObject*>("vertex_line_" + vert->n1->name + vert->n2->name))->line->setPen(pen);
            }
        }
    }
    void select_node(const QString& name, graph* gr) {
        if (s_p1 && s_p2) {
            reset();
        }
        if (s_p1 == nullptr) {
            s_p1 = node_map[name];
            this->findChild<QLabel*>("begin_label")->setText("Начало: " + s_p1->name);
            return;
        }
        if (s_p2 == nullptr && name != s_p1->name) {
            s_p2 = node_map[name];
            this->findChild<QLabel*>("end_label")->setText("Конец: " + s_p2->name);
            saved_path = gr->find_path(s_p1->name, s_p2->name);

            auto out = this->findChild<QLineEdit*>("output");
            if (saved_path.size() == 0) {
                out->setText("Пути не существует");
            } else {
                QString text = s_p1->name + " - ";
                node* last_node = s_p1;
                QPen pen = QPen(QColorConstants::Svg::lightblue);
                pen.setWidth(16);
                for (auto vert : saved_path) {
                    static_cast<line_holder*>(this->findChild<QObject*>("vertex_line_" + vert->n1->name + vert->n2->name))->line->setPen(pen);
                    auto select_node = (vert->n1 == last_node? vert->n2 : vert->n1);
                    last_node = select_node;
                    text += select_node->name;
                    if (select_node != s_p2) {
                        text += " - ";
                    }
                }
                out->setText(text);
                this->findChild<QPushButton*>("save_button")->setDisabled(false);
            }
            return;
        }
    }
};

vertex* connect_nodes(const QString& p1, const QString& p2, float len = 1) {
    if (p1 == p2) {
        return nullptr;
    }
    return new vertex(node_map[p1], node_map[p2], len);
}

void draw_line(vertex* v, QGraphicsView* gview) {

    double len = v->length;
    double total = v->coef * len;

    QPointF e1_rect = static_cast<button_elipse_holder*>(gview->findChild<QPushButton*>("button_node_" + v->n1->name))->ellipse->rect().center();
    QPointF e2_rect = static_cast<button_elipse_holder*>(gview->findChild<QPushButton*>("button_node_" + v->n2->name))->ellipse->rect().center();
    QGraphicsLineItem* line;
    QLine l = QLine(e1_rect.x(), e1_rect.y(), e2_rect.x(), e2_rect.y());
    QPen pen;
    if (v->coef < 1.2) {
        pen = QPen(QColorConstants::Svg::lightgreen);
    } else if (v->coef < 1.9) {
        pen = QPen(QColorConstants::Svg::orange);
    } else if (v->coef < 3.3) {
        pen = QPen(QColorConstants::Svg::red);
    } else {
        pen = QPen(QColorConstants::Svg::mediumpurple);
    }
    pen.setWidth(4);

    line = gview->scene()->addLine(l, pen);
    auto disp = new QLabel(gview);
    disp->setObjectName("vertex_disp_" + v->n1->name + v->n2->name);
    disp->setText(v->n1->name + v->n2->name + ": " + QString::number(len) + "(" + QString::number(total) + ")");
    disp->move(l.center().x(), l.center().y());
    disp->resize(200,20);
    auto lh = new line_holder(line, gview);
    lh->setObjectName("vertex_line_" + v->n1->name + v->n2->name);
}

int main(int argc, char *argv[])
{
    rng.seed(std::time(0));
    QApplication a(argc, argv);
    auto widget = new mainwindow();
    auto scene = new QGraphicsScene(QRect(0,0,1000,1000));
    auto gview = new QGraphicsView(scene, widget);
    gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    std::vector<QPoint> node_points = {
        QPoint(10, 50),
        QPoint(10,160),
        QPoint(140, 70),
        QPoint(300, 150),
        QPoint(50, 430),
        QPoint(190, 510),
        QPoint(200, 290),
        QPoint(402, 40),
        QPoint(600, 140),
        QPoint(600,700),
        QPoint(700,600),
        QPoint(800,900),
        QPoint(750,750)
    };
    QString alpha = "ABCDEFGHIJKLMNOPQRTUVWXYZ";
    graph* gr = new graph();
    int current_alpha = 0;
    for (auto point : node_points) {
        int name_symbol = current_alpha;
        QString name = alpha[name_symbol];
        node_map[name] = new node(name);
        auto b = new button_elipse_holder(name, gview);
        b->connect(b, &button_elipse_holder::clicked, [=]() {widget->select_node(name, gr);});
        b->ellipse = scene->addEllipse(point.x(), point.y(), 30, 30);
        b->resize(20,20);
        b->move(point - QPoint(-7, 12));
        b->setObjectName(QString("button_node_") + name);


        current_alpha++;
    }

    gr->verteces.emplace_back(connect_nodes("A", "B"));
    gr->verteces.emplace_back(connect_nodes("B", "C"));
    gr->verteces.emplace_back(connect_nodes("A", "C"));
    gr->verteces.emplace_back(connect_nodes("C", "D"));
    gr->verteces.emplace_back(connect_nodes("B", "G", 2));
    gr->verteces.emplace_back(connect_nodes("B", "E", 3));
    gr->verteces.emplace_back(connect_nodes("C", "H", 2));
    gr->verteces.emplace_back(connect_nodes("H", "I", 1.5));
    gr->verteces.emplace_back(connect_nodes("F", "I", 5));
    gr->verteces.emplace_back(connect_nodes("E", "F"));
    gr->verteces.emplace_back(connect_nodes("E", "G"));
    gr->verteces.emplace_back(connect_nodes("D", "I", 3));
    gr->verteces.emplace_back(connect_nodes("G", "D"));
    gr->verteces.emplace_back(connect_nodes("G", "I", 4));
    gr->verteces.emplace_back(connect_nodes("K", "J"));
    gr->verteces.emplace_back(connect_nodes("J", "M"));
    gr->verteces.emplace_back(connect_nodes("K", "M"));
    gr->verteces.emplace_back(connect_nodes("M", "L"));

    for (auto vert : gr->verteces) {
        draw_line(vert, gview);
    }

    auto begin_label = new QLabel("Начало: ", widget);
    begin_label->setObjectName("begin_label");
    begin_label->resize(200, 30);
    begin_label->move(QPoint(1050, 30));

    auto end_label = new QLabel("Конец: ", widget);
    end_label->setObjectName("end_label");
    end_label->resize(200, 30);
    end_label->move(QPoint(1050, 60));

    auto output = new QLineEdit(widget);
    output->setObjectName("output");
    output->move(QPoint(1050, 90));
    output->resize(150, 30);

    auto reroll_button = new QPushButton("↺", widget);
    reroll_button->move(QPoint(1100, 0));
    reroll_button->connect(reroll_button, &QPushButton::clicked, [=]() {gr->reroll_coefs(gview); widget->reset(false);});

    auto save_button = new QPushButton("Сохранить", widget);
    save_button->setObjectName("save_button");
    save_button->setGeometry(1075, 125, 100, 20);
    save_button->setDisabled(true);
    save_button->connect(save_button, &QPushButton::clicked, [=]() {std::ofstream out("path.txt"); out.clear(); out << output->text().toStdString();});
    output->connect(output, &QLineEdit::textChanged, [=]() {save_button->setDisabled(true);});

    widget->setGeometry(QRect(0,0, 1250, 1200));
    widget->show();


    return QApplication::exec();
}
