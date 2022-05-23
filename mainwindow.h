#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "buisness_logic.h"
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QPainter>
#include "PaintWidget.h"

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
    void on_pushButton_calc_metr_clicked();
    void on_pushButton_load_clicked();
    void on_pushButton_print_region_clicked();

private:

    unsigned int numberColumns = 0;
    unsigned int numberLines = 0;
    Ui::MainWindow *ui;
    vector <string> headers;
    vector <string> republics;
    vector <vector<string>> dateVector;
    double *data = nullptr;
    PaintWidget *graph_paint = nullptr;
    void reset();
    void createItem(std::string str, int row, int column);
    void outputTable();
    void setSizeColumToDefault();
    void forForColumnNumber();

};
#endif // MAINWINDOW_H
