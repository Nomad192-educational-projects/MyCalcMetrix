#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <math.h>

class PaintWidget : public QWidget
{
public:
    PaintWidget(QWidget *parent, double *data = nullptr, unsigned int numberYears = 0, double max=0, double min=0, unsigned int firstYear=1900);

  protected:
    void paintEvent(QPaintEvent *e);

  private:
    double *data;
    unsigned int numberYears;
    double max;
    double min;
    unsigned int firstYear;
    void doPainting();
};

#endif // PAINTWIDGET_H
