#include "card.h"
#include "ui_card.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

card::card(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::card)
{
    ui->setupUi(this);
}

card::card(entity* ptr, MainWindow* mw, Ui::MainWindow* mw_ui, QListWidgetItem* item)
    : ui(new Ui::card)
{
    _mw = mw;
    _mw_ui = mw_ui;
    _ptr = ptr;
    _item = item;

    ui->setupUi(this);
    _ptr->Craft(ui);
    mw->setEnabled(false);
}

card::~card()
{
    _mw->setEnabled(true);
    delete ui;
}

void card::on_card_destroyed()
{
    _mw->setEnabled(true);
}


void card::on_cancel_pressed()
{
    _mw->setEnabled(true);
    delete this;
}


void card::on_print_pressed()
{
    _mw->entities.erase(_mw->entities.begin() + _mw_ui->list->row(_item));
    delete _ptr;
    _mw_ui->list->takeItem(_mw_ui->list->row(_item));
    delete _item;
    _mw->setEnabled(true);
    delete this;
}

