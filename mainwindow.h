#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "buisnesslogic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_file_clicked();
    void on_pushButton_load_clicked();
    void on_pushButton_calc_metr_clicked();

private:
    Ui::MainWindow *ui;
    BuisnessLogic * bl;
    QStringList headers;
    int number_colums = 0;
    int number_rows = 0;
    void reset();
    void reset_table();
};
#endif // MAINWINDOW_H
