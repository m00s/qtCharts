#include "histogramm.h"
#include <QLinearGradient>
#include <math.h>

histogramm::histogramm(myData* n) : Chart(), _Values(n){
}

histogramm::~histogramm(){
    //pieces.clear();
}

void histogramm::draw(QPainter *painter){
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    double pDist = 10;
    double pW = (cW-(pieces.size())*pDist)/pieces.size();
    QLinearGradient gradient(cX+cW/2,cY,cX+cW/2,cY+cH);
    gradient.setColorAt(0,Qt::black);
    QPen pen;
    pen.setWidth(3);

    for (int i=0; i<pieces.size(); i++)
    {
        // Shadows
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::darkGray);
        painter->drawRect(cX+pDist+i*(pW + pDist)-pDist/2,cY+cH-1,pW,-cH/100*pieces[i].pPerc+pDist/2);

        gradient.setColorAt(1,pieces[i].rgbColor);
        painter->setBrush(gradient);
        pen.setColor(pieces[i].rgbColor);
        painter->setPen(pen);
        painter->drawRect(cX+pDist+i*(pW + pDist), cY+cH-2,pW,-cH/100*pieces[i].pPerc+pDist/2-4);
        QString label = (QString("%L1").arg(pieces[i].pPerc,0,'f',1)) +"%";
        painter->setPen(Qt::SolidLine);
        painter->drawText(cX+pDist+i*(pW + pDist)+pW/2-painter->fontMetrics().width(label)/2, cY+cH-cH/100*pieces[i].pPerc-painter->fontMetrics().height()/2, label);
    }
    painter->setPen(Qt::SolidLine);
    for (int i=1;i<10;i++){
        painter->drawLine(cX-3,cY+cH/10*i,cX+3,cY+cH/10*i);
        // VALORI % ASSE DELLE ORDINATE
        painter->drawText(cX-30,cY+cH/10*i,QString::number((10-i)*10));
    }
    painter->drawLine(cX,cY+cH,cX,cY);
    painter->drawLine(cX,cY,cX+4,cY+10);
    painter->drawLine(cX,cY,cX-4,cY+10);
    painter->drawLine(cX,cY+cH,cX+cW,cY+cH);
}

void histogramm::drawLegend(QPainter *painter){
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
        painter->drawRect(x,y,painter->fontMetrics().height(),painter->fontMetrics().height());
        painter->drawText(x+painter->fontMetrics().height()+dist,y+painter->fontMetrics().height()/2+dist, QString(pieces[i].pname + ": " + QString::number(_Values->atIndex(i))));
    }
}
