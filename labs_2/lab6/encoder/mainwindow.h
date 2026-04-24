#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../shared/inc.h"

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

private slots:
    void on_add_to_json_clicked();

    void on_name_line_textEdited(const QString &arg1);

    void on_desc_line_textEdited(const QString &arg1);

    void on_coef_line_textEdited(const QString &arg1);

    void on_type_line_textEdited(const QString &arg1);

    void on_txt_insert_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
