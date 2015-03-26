#ifndef CHART_H
#define CHART_H
#include <QPoint>
#include <QString>
#include <QColor>
#include <QPainter>

class Chart
{
protected:
    class chartPiece {
    public:
        explicit chartPiece();
        void addName(QString name);
        void setColor(QColor color);
        void setPerc(float Percentage);
        QString pname;
        QColor rgbColor;
        float pPerc;
    };
protected:
    double cX,cY,cW,cH,pW,lX,lY;
    QVector<chartPiece> pieces;
public:
    ~Chart();
    Chart();
    void setCoordinates(double, double, double, double);
    void addPiece(QString, QColor, float);
    //DUE METODI VIRTUALI PURI
    virtual void draw(QPainter *painter) = 0;
    virtual void drawLegend(QPainter *painter) = 0;
};

#endif // CHART_H
