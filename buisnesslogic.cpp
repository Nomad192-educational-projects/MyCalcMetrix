#include "buisnesslogic.h"

BuisnessLogic::BuisnessLogic()
{

}

void BuisnessLogic::open_file(QFile *f)
{
    this->f = f;
}

void BuisnessLogic::download_colums(int * numbers_colums, QStringList * headers)
{

    QByteArray line = f->readLine();
    auto parts = line.split(',');
    *numbers_colums = parts.size()+1;
    for(int i = 0; i < parts.length(); i++)
    {
        headers->append(parts[i]);
    }
}


void BuisnessLogic::download_lines(int *number_rows, QList<QByteArray> * republics)
{
    QByteArray line = f->readLine();
    auto parts = line.split(',');
    number_years++;
    int year = parts.first().toInt();
    dateList.append(parts);
    republics->append(parts[1]);
    qDebug() << parts;
    number_republics++;

    while (!f->atEnd())
    {
        line = f->readLine();
        parts = line.split(',');
        int current_year = parts.first().toInt();
        if(current_year != year)
        {
            number_years++;
            year = current_year;
            break;
        }
        dateList.append(parts);
        republics->append(parts[1]);
        number_republics++;
        qDebug() << parts;
    }

    while(!f->atEnd())
    {
        parts = line.split(',');
        int current_year = parts.first().toInt();
        if(current_year != year)
        {
            number_years++;
            year = current_year;
        }

        dateList.append(parts);
        qDebug() << parts;

        line = f->readLine();
    }
    *number_rows = number_years;
}

void BuisnessLogic::calc_metr(int metrix, int republic, double *min, double *med, double *max)
{

    qDebug() << republic;

    double data[number_years];

    QDebug deb = qDebug();
    deb.nospace();
    deb << "\n-----------all----------\n";
    for (int i = 0; i < number_years; i++)
    {
        data[i] = dateList[i*number_republics + republic][metrix].toDouble();
        deb  << data[i] << " ";
    }
    deb << "\n-----------all----------\n";

    for (int i = 0; i < number_years - 1; i++)
    {
        for (int y = i + 1; y < number_years; y++)
        {
            if(data[i] > data[y])
            {
                double buffer = data[i];
                data[i] = data[y];
                data[y] = buffer;
            }
        }
    }
    deb << "\n-----------sort----------\n";
    for (int i = 0; i < number_years; i++)
    {
        deb  << data[i] << " ";
    }
    deb << "\n-----------sort----------\n";

    *min = data[0];
    *max=data[number_years - 1];

    if(number_years%2 == 0)
    {
        *med = data[number_years/2] + data[number_years/2 - 1];
        *med /= 2;
    }
    else
        *med = data[number_years/2];
}

void BuisnessLogic::load_data(int republic, QList <QList <QByteArray>> * data_table)
{
    for (int i = 0; i < number_years; i++)
    {
        data_table->append(dateList[i*number_republics + republic]);
    }
}
