#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include "./lib/chart.h"
#include "./lib/mydata.h"

class histogramm : public Chart{
public:
    explicit histogramm(myData*);
    ~histogramm();
	void draw(QPainter *painter);
    void drawLegend(QPainter *painter);
private:
    myData* _Values;
};

#endif
