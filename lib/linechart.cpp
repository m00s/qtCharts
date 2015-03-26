#include "linechart.h"

lineChart::lineChart(myData* n) : Chart(), _Values(n){
}

lineChart::~lineChart(){
}

void lineChart::draw(QPainter *painter){
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    double pDist = 30;
    double pW = (cW-(pieces.size())*pDist)/pieces.size();
    int varText=10;
    QPen pen;
    pen.setWidth(3);
    QString label;
    for (int i=0; i<pieces.size()-1; i++)
    {
        QPoint p1(cX+pDist+i*(pW + pDist), cY+cH-cH/100*pieces[i].pPerc-5);
        QPoint p2(cX+pDist+(i+1)*(pW + pDist), cY+cH-cH/100*pieces[i+1].pPerc-5);
        //SE LA LINEA SALE IL TESTO VA SOTTO IL PUNTO, ALTRIMENTI SOPRA
        varText=10;
        if(_Values->atIndex(i) > _Values->atIndex(i+1))
            varText=-10;
        painter->setPen(Qt::SolidLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
        label = QString::number(_Values->atIndex(i));
        painter->drawText(cX+pDist+i*(pW + pDist)+5, cY+cH-cH/100*pieces[i].pPerc+varText, label);
        pen.setColor(Qt::blue); // || pieces[i].rgbColor
        painter->setPen(pen);
        painter->drawLine(p1, p2);
        pen.setColor(Qt::yellow);
        painter->setPen(pen);
        painter->drawPoint(p1);
    }
    pen.setColor(Qt::yellow);
    painter->setPen(pen);
    painter->drawPoint(cX+pDist+(pieces.size()-1)*(pW + pDist), cY+cH-cH/100*pieces[pieces.size()-1].pPerc-5);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    label = QString::number(_Values->atIndex(pieces.size()-1));
    painter->drawText(cX+pDist+(pieces.size()-1)*(pW + pDist)+5, cY+cH-cH/100*pieces[pieces.size()-1].pPerc+varText, label);
    painter->setPen(Qt::SolidLine);
    for (int i=1;i<10;i++){
        painter->drawLine(cX-3,cY+cH/10*i,cX+3,cY+cH/10*i);
    }
    painter->drawLine(cX,cY+cH,cX,cY);
    painter->drawLine(cX,cY,cX+4,cY+10);
    painter->drawLine(cX,cY,cX-4,cY+10);
    painter->drawLine(cX,cY+cH,cX+cW,cY+cH);
}

void lineChart::drawLegend(QPainter *painter){
    int add = 0;
    if(pieces.count() > 9)
        add = 10 + 15*(pieces.count()-10);
    painter->setPen(Qt::SolidLine);
    int dist = 5;
    painter->setBrush(Qt::white);
    for (int i=pieces.size()-1;i>=0;i--)
    {
        painter->setBrush(pieces[i].rgbColor);
        float x = lX+dist;
        float y = lY+dist-add+i*(painter->fontMetrics().height()+2*dist);
        painter->drawText(x+painter->fontMetrics().height()+dist,y+painter->fontMetrics().height()/2+dist, QString(pieces[i].pname + ": " + QString::number(_Values->atIndex(i))));
    }
}
