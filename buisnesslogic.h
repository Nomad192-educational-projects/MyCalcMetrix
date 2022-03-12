#ifndef BUISNESSLOGIC_H
#define BUISNESSLOGIC_H

#include <QFileDialog>

class BuisnessLogic
{
public:
    BuisnessLogic();

    void open_file(QFile *f);
    void download_colums(int * number_colums, QStringList * headers);
    void download_lines(int *number_rows, QList<QByteArray> * republics);
    void calc_metr(int metrix, int republic, double *min, double *med, double *max);
    void load_data(int republic, QList <QList <QByteArray>> * data_table);

private:
    QFile *f = nullptr;
    QList <QList <QByteArray>> dateList;
    int number_years=0;
    int number_republics=0;
};

#endif // BUISNESSLOGIC_H
