#ifndef LINECHART_H
#define LINECHART_H
#include "./lib/chart.h"
#include "./lib/mydata.h"

class lineChart : public Chart{
public:
    explicit lineChart(myData*);
    ~lineChart();
    void draw(QPainter *painter);
    void drawLegend(QPainter *painter);
private:
    myData* _Values;
};

#endif
