#ifndef CARD_H
#define CARD_H
#include "lib.h"
#include "card.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QListWidgetItem>
class entity;

class MainWindow;

namespace Ui {
class card;
}

class card : public QWidget
{
    Q_OBJECT
public:
    friend class enemy;
    explicit card(QWidget *parent = nullptr);
    explicit card(entity* ptr, MainWindow* mw, Ui::MainWindow* mw_ui, QListWidgetItem* item);
    ~card();
    Ui::card *ui;
private slots:
    void on_card_destroyed();
    void on_cancel_pressed();

    void on_print_pressed();

private:
    MainWindow* _mw = nullptr;
    Ui::MainWindow* _mw_ui = nullptr;
    entity* _ptr = nullptr;
    QListWidgetItem* _item = nullptr;
};

#endif // CARD_H
