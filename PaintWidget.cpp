#include "PaintWidget.h"
#include <QApplication>
#include <QPainter>


PaintWidget::PaintWidget(QWidget *parent, double *data, unsigned int numberYears, double max, double min, unsigned int firstYear)
    : QWidget(parent)
{

    this->data = data;
    this->numberYears = numberYears;
    this->max = max;
    this->min = min;
    this->firstYear = firstYear;
}

void PaintWidget::paintEvent(QPaintEvent *e) {

  Q_UNUSED(e);

  doPainting();
  qDebug() << "paint";
}

void PaintWidget::doPainting() {
    QPainter p(this); //объект для рисования

    int x=this->width()/2, y=this->height()/2; //центр окна
    qDebug() << x << " " << y;
    int yMax;
    int yMin;
    int yX;

    if(max <= 0)
    {
        yMax = this->height()/abs(min) * abs(max);
        yMin = this->height();
        yX = 0;
    }
    else if(min < 0)
    {
        yMax = 0;
        yMin = this->height();
        yX = this->height()/(max + abs(min)) * max;
    }
    else
    {
        yMax = 0;
        yMin = this->height()/max * min;//(max - min);
        yX = this->height() - 20;
    }



    //p.setPen (QPen(Qt::blue,Qt::SolidLine));

    //p.setPen (QPen(Qt::red,Qt::SolidLine));


    QFont font("Arial",-1,-1, false);
    font.setPixelSize(10);
    p.setFont(font); //зададим свойства шрифта
    p.setPen (QPen(QColor(0,100,50,255),Qt::SolidLine)); //цвет и тип пера

    int h_text = 10, w_text = this->width()/numberYears;
    qDebug() << w_text;
    qDebug() << min << " " << max;

    p.drawLine(w_text, 0, w_text, 2*y); //координатные y
    p.drawLine(0, yX, 2*x, yX); //координатные x

    {
        QRect rect(0, yMax+5, w_text, h_text);//прямоугольник для текста
        p.drawText(rect, Qt::AlignCenter, QString::number(max));
    }
    {
        QRect rect(0, yMin-5-h_text, w_text, h_text);//прямоугольник для текста
        p.drawText(rect, Qt::AlignCenter, QString::number(min));
    }


    for(unsigned int i = 0; i < numberYears; i++)
    {
        QRect rect(w_text + w_text*i, yX+5, w_text, h_text);//прямоугольник для текста
        p.drawText(rect, Qt::AlignCenter, QString::number(firstYear+i));
    }

    /*qDebug() << "isinf(" << this->data[0] << ")=" << isinf(this->data[0]);
    if(!isinf(this->data[0]))
    {
        p.drawPoint(w_text*0 + w_text/2, (max-this->data[0])/(max - min)*(yMin - yMax));
        qDebug() << this->data[0] << " " << (max-this->data[0])/(max - min)*(yMin - yMax);
    }*/
    for(unsigned int i = 1; i < numberYears; i++)
    {
        qDebug() << "isinf(" << this->data[i] << ")=" << isinf(this->data[i]);
        if(!isinf(this->data[i]))
        {
            p.drawPoint(w_text + w_text*i + w_text/2, yMax+5+(max-this->data[i])/(max - min)*(yMin - 5 - yMax));
            qDebug() << this->data[i] << " " << (max-this->data[i])/(max - min)*(yMin - yMax);
            if (!isinf(this->data[i-1]))
            {
                p.drawLine(w_text + w_text*(i-1) + w_text/2, yMax+5+(max-this->data[i-1])/(max - min)*(yMin - 5 - yMax), w_text + w_text*i + w_text/2, yMax+5+(max-this->data[i])/(max - min)*(yMin - 5 - yMax));
            }
            else
            {
                qDebug() << "value-1 is inf";
            }
        }
        else
        {
            qDebug() << "value is inf";
        }

    }

/*построение графика*/
    /*for(int i=0; i<1800000; i++)
    {
        f = -qCos(k*(dx-x))*a + y;
        p.drawPoint(dx,f);
        dx = dx + h;
    }*/
}
