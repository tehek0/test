#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QLine>
#include <QPen>
#include <QRect>
#include <QString>
#include <QPushButton>
#include <QRandomGenerator>
#include <map>


struct node {
    QString name;
    node(const QString& _name): name(_name) {}
};

struct vertex {
    node* n1 = nullptr;
    node* n2 = nullptr;
    float length;
    float coef;
    vertex(node* b, node* d, float l): n1(b), n2(d), length(l), coef(1) {}
};

class graph {
public:
    std::vector<vertex*> verteces;
    graph() = default;

};

class button_elipse_holder : public QPushButton {


public:
    QGraphicsEllipseItem* ellipse = nullptr;
    button_elipse_holder(const QString& text, QWidget* parent) : QPushButton(text, parent) {}
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto widget = new QWidget();
    auto scene = new QGraphicsScene(QRect(0,0,1000,1000));
    auto gview = new QGraphicsView(scene, widget);
    gview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    std::vector<QPoint> node_points = {
        QPoint(10, 50),
        QPoint(10,100),
        QPoint(40, 70),
        QPoint(100, 50),
        QPoint(120, 90),
        QPoint(50, 230),
        QPoint(90, 210),
        QPoint(200, 60),
        QPoint(152, 40),
        QPoint(300, 90)
    };
    QString alpha = "ABCDEFGHIJKLMNOPQRTUVWXYZ";
    graph gr = graph();
    int current_alpha = 0;
    for (auto point : node_points) {
        auto b = new button_elipse_holder(alpha[current_alpha], gview);
        b->ellipse = scene->addEllipse(point.x(), point.y(), 30, 30);
        b->resize(20,20);
        b->move(point - QPoint(-7, 10));
        b->setObjectName(QString("button_node_") + alpha[current_alpha]);
        current_alpha++;
    }

    // QGraphicsEllipseItem* elipse1 = scene->addEllipse(100, 100, 30, 30);
    // QGraphicsEllipseItem* elipse2 = scene->addEllipse(110, 150, 30, 30);
    // QGraphicsLineItem* line = scene->addLine(QLine(elipse1->rect().center().x(), elipse1->rect().center().y(), elipse2->rect().center().x(), elipse2->rect().center().y()), QPen(Qt::green));



    widget->setGeometry(QRect(0,0, 1200, 1200));
    widget->show();


    return QApplication::exec();
}
