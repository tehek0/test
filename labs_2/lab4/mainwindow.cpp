#include "mainwindow.h"
#include "ui_mainwindow.h"

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







void MainWindow::on_author_textEdited(const QString &arg1)
{
    size_t cursorpos = ui->author->cursorPosition();
    if (cursorpos > 0) {
        --cursorpos;
    }
    if (arg1.size() == 0) {
        return;
    }
    qInfo() << (int)(arg1.toStdString()[cursorpos]);
}



void MainWindow::on_discard_pressed()
{
    ui->author->clear();
    ui->name->clear();
    ui->code->clear();
    ui->contents->clear();
    ui->type_paper->setAutoExclusive(false);
    ui->type_paper->setChecked(false);
    ui->type_paper->setAutoExclusive(true);
    ui->type_digital->setAutoExclusive(false);
    ui->type_digital->setChecked(false);
    ui->type_digital->setAutoExclusive(true);
    ui->genre_detective->setChecked(false);
    ui->genre_fiction->setChecked(false);
    ui->genre_novel->setChecked(false);

}

