#include "tree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tree x = tree();
    x.draw();
    return QApplication::exec();
}
