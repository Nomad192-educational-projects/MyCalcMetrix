#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "buisnesslogic.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_load->setEnabled(false);
    ui->pushButton_calc_metr->setEnabled(false);
    ui->comboBox_region->setEnabled(false);
    ui->comboBox_column_number->setEnabled(false);
    //bl = new BuisnessLogic();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bl;
}


void MainWindow::reset()
{
    delete bl;
    bl = new BuisnessLogic();
    number_colums = 0;
    number_rows = 0;
    headers.clear();

    ui->comboBox_column_number->clear();
    ui->comboBox_region->clear();
}

void MainWindow::reset_table()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setRowCount(number_rows);
    ui->tableWidget->setColumnCount(number_colums-1);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void MainWindow::on_pushButton_file_clicked()
{
    QFile *f = new QFile(QFileDialog::getOpenFileName(this,
                                               tr("Open File"),
                                               "",
                                               tr("Data Files (*.csv)")));
    if (f->fileName().isNull())
    {
        ui->textBrowser_name_file->setText("No file selected!");
    }
    else
    {
        QFileInfo fileInfo(f->fileName());
        ui->textBrowser_name_file->setText(fileInfo.fileName());
        ui->comboBox_region->setEnabled(true);

        if(!f->open(QIODevice::ReadOnly))
        {
            qDebug() << f->errorString();
            ui->textBrowser_name_file->setText(f->errorString());
        }
        else
        {
            reset();

            bl->open_file(f);
            bl->download_colums(&number_colums, &headers);
            for(int i = 3; i < number_colums; i++)
            {
                ui->comboBox_column_number->addItem(QString::number(i));
                qDebug() << i;
            }
            if(ui->comboBox_column_number->count() == 0)
            {
                qDebug() << "Error: not foud metrix";
                ui->textBrowser_name_file->setText("Error: not foud metrix");
            }
            else
            {
                ui->comboBox_column_number->setEnabled(true);
            }

            QList <QByteArray> * republics = new QList <QByteArray>;
            bl->download_lines(&number_rows, republics);

            for(int i = 0; i < republics->length(); i++)
            {
                ui->comboBox_region->addItem(republics->at(i));
                qDebug() << republics->at(i);
            }

            delete republics;

            qDebug() << headers;

            reset_table();

            if(ui->comboBox_region->count() != 0)
            {
                ui->comboBox_region->setEnabled(true);
                ui->pushButton_calc_metr->setEnabled(true);
                ui->pushButton_load->setEnabled(true);
            }
            else
            {
                qDebug() << "Error: not foud regions";
                ui->textBrowser_name_file->setText("Error: not foud regions");
            }
        }
    }

    delete f;
}


void MainWindow::on_pushButton_load_clicked()
{
    /*int n_row = ui->tableWidget->rowCount();
    for(int row=0; row!=n_row; ++row){
       ui->tableWidget->removeRow(row);
    }
    ui->tableWidget->setRowCount(number_rows);*/

    int republic = ui->comboBox_region->currentIndex();

    qDebug() << republic;

    QList <QList <QByteArray>> data_table;
    bl->load_data(republic, &data_table);

    for(int row=0; row!=ui->tableWidget->rowCount(); ++row){
        qDebug() << data_table[row];
        for(int column=0; column!=ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(data_table[row][column]));
            ui->tableWidget->setItem(row, column, newItem);
        }
    }

    //QFile file("FlightParam.csv");

    /*if(f == nullptr || !f->open(QIODevice::ReadOnly))
    {
        if (f != nullptr)
        {
            qDebug() << f->errorString();
            ui->textBrowser_name_file->setText(f->errorString());
        }
        else
        {
            qDebug() << "No file selected!";
            ui->textBrowser_name_file->setText("No file selected!!");
        }
        return;
    }

    QStringList wordList;
    while (!f->atEnd()) {
        QByteArray line = f->readLine();
        wordList.append(line.split(',').first());
    }

    for(int i = 1; i < 5; i++)
    {
        ui->comboBox_column_number->addItem(QString::number(i));
    }


    qDebug() << wordList;

    return;*/
}


void MainWindow::on_pushButton_calc_metr_clicked()
{
    int metrix = ui->comboBox_column_number->currentText().toInt() - 1;
    int republic = ui->comboBox_region->currentIndex();

    double min, med, max;

    bl->calc_metr(metrix, republic, &min, &med, &max);

    ui->textBrowser_min->setText(QString::number(min));
    ui->textBrowser_max->setText(QString::number(max));
    ui->textBrowser_med->setText(QString::number(med));

}

