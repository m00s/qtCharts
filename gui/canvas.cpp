#include "canvas.h"
#include "chartsheet.h"
#include "./lib/pieChart.h"
#include "./lib/histogramm.h"
#include "./lib/linechart.h"
#include <QMouseEvent>
#include <QMenu>
#include <QDebug>

int canvas::movex = 375;
int canvas::movey = 150;

canvas::canvas(myData* n, Chart* t, QWidget *parent) : QWidget(parent), graph(t), _Values(n) {
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->move((movex+=15)%750, (movey+=5)%300);
    setSize();
    this->show();
    del = menu.addAction("Delete");
    chartSheet* p = static_cast<chartSheet*>(this->parent());
    connect(del, SIGNAL(triggered()) , this, SLOT(remove()));
    connect(this, SIGNAL(removeThis()) , p, SLOT(removeCanvas()));
}

canvas::~canvas(){
    delete graph;
    qDebug() << "Distruttore canvas";
}

void canvas::remove(){
    movex-=15; movey-=5;
    emit removeThis();
}

void canvas::paintEvent(QPaintEvent *){
    QPainter painter(this);
    graph->draw(&painter);
    graph->drawLegend(&painter);
}

void canvas::draw(){
    update();
}

void canvas::setSize(){
    //RTTI per setFixedSize();
    pieChart* p = dynamic_cast<pieChart*>(graph);
    if(p){ // pieChart
        if(_Values->count()==1){
            setFixedSize(550, 500);
            graph->setCoordinates(200,100,250,250);
        }
        else{
            if(_Values->count()>9){
                setFixedSize(750, 680);
                graph->setCoordinates(200,150,350,350);
            }
            else{
                setFixedSize(550, 500);
                graph->setCoordinates(150, 100, 250, 250);
            }
        }
    }
    else{ // Histogramm | lineChart
        if(_Values->count()>9){
            setFixedSize(750, 400);
            graph->setCoordinates(50,100,550,250);
        }
        else{
            setFixedSize(600, 400);
            graph->setCoordinates(50,100,400,250);
        }
    }
}

void canvas::mousePressEvent(QMouseEvent *evt){
    if(evt->button() ==  Qt::RightButton )
        menu.exec(evt->globalPos());
    else
        oldPos = evt->globalPos();
}

void canvas::mouseMoveEvent(QMouseEvent *evt){
    const QPoint delta = evt->globalPos() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = evt->globalPos();
}
