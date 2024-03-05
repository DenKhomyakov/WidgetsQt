#ifndef AREA_H
#define AREA_H

#include "figura.h"
#include <QWidget>

class Area : public QWidget
{
    int myTimer;
    float alpha;

public:
    Area(QWidget *parent = 0);

    ~Area();

    MyLine *myline;
    MyRect *myrect;

protected:

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
};

#endif
