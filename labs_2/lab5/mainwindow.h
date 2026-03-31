#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib.h"
#include <vector>
#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::vector<entity*> entities;

private slots:
    void on_load_pressed();

    void on_list_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
