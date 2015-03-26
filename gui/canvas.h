#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMenu>
#include "./lib/mydata.h"
#include "./lib/chart.h"

const int MAXCOLORS = 40;

class canvas : public QWidget
{
    static int movex;
    static int movey;
    Q_OBJECT
    Chart* graph;
    myData* _Values;
    QPoint oldPos;
    void setSize();
    QMenu menu;
    QAction* del;
public:
    explicit canvas(myData* , Chart*, QWidget *parent = 0);
    ~canvas();
protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);

signals:
    void removeThis();
private slots:
    void remove();
public slots:
    void draw();
};

#endif // CANVAS_H
