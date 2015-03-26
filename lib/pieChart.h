#ifndef PIECHART_H
#define PIECHART_H
#include <QPainter>
#include <math.h>
#include "chart.h"

class pieChart : public Chart {
    QPointF getPnt(double angle, double R1 = 0, double R2 = 0);
    int getQtr(double angle);
    double Angle360(double angle);
    double palpha;
public:
	explicit pieChart();
    ~pieChart();
    virtual void draw(QPainter *painter);
    virtual void drawLegend(QPainter *painter);
};

#endif
