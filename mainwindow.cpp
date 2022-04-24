#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->pushButton_load->setEnabled(false); //блокировка лоад дата
    ui->pushButton_calc_metr->setEnabled(false);//блокировка кнопки метрик
    ui->comboBox_region->setEnabled(false);//блокировка комбобокса регионов
    ui->comboBox_column_number->setEnabled(false);//блокировка комбобокса колонок
    setSizeColumToDefault();//растяжка колонок в таблице при открытии?
}


MainWindow::~MainWindow(){
    delete ui; //удаляем копию класса ui
    delete[] data;
}

void MainWindow::on_pushButton_file_clicked(){ //функция отклика open file
    QFile *f = new QFile(QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Data Files (*.csv)"))); //путь файла и имя:)//создаем указатель на файл типа QFile
    if(!f->fileName().isNull()){ //isNull  проверка на инициализации
        QFileInfo fileInfo(f->fileName());//QFileInfo информация об имени и полоэении файла, берем имя файла
        ui->textBrowser_name_file->setText(fileInfo.fileName()); //встевляем имя файла в текст браузер
        string name = (f->fileName()).toStdString();//создаем переменную name, берем имя файла и переделываем в стд
        reset();
        if (interfaceBundle(OPEN_FILE, &name, &headers, &republics, &numberLines, &dateVector)){
            forForColumnNumber();
            for(int i = 0; i < (int)republics.size(); i++){
                ui->comboBox_region->addItem(QString::fromStdString(republics.at(i)));
            }

            if(ui->comboBox_region->count() == 0){
                ui->textBrowser_name_file->setText("Not found regions!");
            }else{
                 ui->comboBox_region->setEnabled(true);
                 ui->pushButton_calc_metr->setEnabled(true);
                 ui->pushButton_load->setEnabled(true);
            }
        }else{
            ui->textBrowser_name_file->setText(f->errorString());
            qDebug() << f->errorString();
        }
    }else{
        ui->textBrowser_name_file->setText("No file celected!");
        reset();
    }
    delete f;
}

void MainWindow::on_pushButton_calc_metr_clicked(){
    ifstream file;
    unsigned int metrix = ui->comboBox_column_number->currentText().toInt() - 1;
    unsigned republic = ui->comboBox_region->currentIndex();
    inMetrix in = {republic, metrix, numberLines, (unsigned int)republics.size()};
    outMetrix out;
    data = new double[in.numberYears];
    interfaceBundle(CALC_METR, &in, &out, data, NULL, &dateVector);
    ui->textBrowser_max->setText(QString::number(out.max));
    ui->textBrowser_med->setText(QString::number(out.med));
    ui->textBrowser_min->setText(QString::number(out.min));

    PaintWidget *myWidget;
    unsigned int firstYear = stoi(dateVector[1][0]);
    myWidget = new PaintWidget(ui->widget, data, in.numberYears, out.max, out.min, firstYear);
    myWidget->resize(ui->widget->width(), ui->widget->height());
    myWidget->show();
}

void MainWindow::forForColumnNumber(){
    for(int i = 3; i < (int)headers.size() + 1; i++){
        ui->comboBox_column_number->addItem(QString::number(i));
    }
    if(ui->comboBox_column_number->count() == 0){
        ui->textBrowser_name_file->setText("Not found metrix!");
    }else{
         ui->comboBox_column_number->setEnabled(true);
    }
}

void MainWindow::reset(){
    dateVector.clear();//очищение памяти
    republics.clear();//очизения республик
    headers.clear();//очищение хедерса
    numberColumns = 0;//
    numberLines = 0;//
    ui->comboBox_column_number->clear();// 83-84 очищение комбобоксов
    ui->comboBox_region->clear();
    ui->comboBox_column_number->setEnabled(false);//85-88 блокировка кнопок
    ui->comboBox_region->setEnabled(false);
    ui->pushButton_calc_metr->setEnabled(false);
    ui->pushButton_load->setEnabled(false);
}

void MainWindow::createItem(std::string str, int row, int column) {//для корректного вывода таблицы  с - и пробелами?
    QTableWidgetItem* item;
    QString qstr = QString::fromStdString(str);
    if (qstr == "") {
        qstr = "-";
    }
    item = new QTableWidgetItem(qstr);
    ui->tableWidget->setItem(row, column, item);
}

void MainWindow::outputTable(){//витзуальная логика для таблицы
    std::vector<std::string> vec;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {//фор вывода таблицы
        std::vector<std::string> vec = dateVector[i];//берем из свидания с вектором строчку
        createItem(vec[0], i, 0);//106-112 вставляем в таблицу итые элементы?
        createItem(vec[1], i, 1);
        createItem(vec[2], i, 2);
        createItem(vec[3], i, 3);
        createItem(vec[4], i, 4);
        createItem(vec[5], i, 5);
        createItem(vec[6], i, 6);

    }
}

void MainWindow::setSizeColumToDefault() {//изначальная растяжка таблицы по окну
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 260);
    ui->tableWidget->setColumnWidth(2, 120);
    ui->tableWidget->setColumnWidth(3, 120);
    ui->tableWidget->setColumnWidth(4, 120);
    ui->tableWidget->setColumnWidth(5, 120);
    ui->tableWidget->setColumnWidth(6, 120);
    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(24);

}

void MainWindow::on_pushButton_load_clicked(){
    //ui->tableWidget->setColumnCount(numberColumns - 1);
    ui->tableWidget->setRowCount(dateVector.size());//количество строк
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);//блокировка ячеек
    ui->tableWidget->setShowGrid(true);//отображается сетка
//    QStringList QHeaders;
//    for(string i:headers){
//        QHeaders.append(QString::fromStdString(i));
//    }
//    ui->tableWidget->setHorizontalHeaderLabels(QHeaders);
      outputTable();//вывод таблицы
}

void MainWindow::on_pushButton_print_region_clicked(){//что тут происходит
    size_t count = 0;
    ui->tableWidget->setRowCount(count);
    for (size_t i = 0; i < dateVector.size(); ++i) {
        if (dateVector[i][1] == ui->comboBox_region->currentText().toStdString()) {
            ui->tableWidget->setRowCount(++count);
            createItem(dateVector[i][0], count - 1, 0);
            createItem(dateVector[i][1], count - 1, 1);
            createItem(dateVector[i][2], count - 1, 2);
            createItem(dateVector[i][3], count - 1, 3);
            createItem(dateVector[i][4], count - 1, 4);
            createItem(dateVector[i][5], count - 1, 5);
            createItem(dateVector[i][6], count - 1, 6);

        }

    }
}

