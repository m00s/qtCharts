#include "chart.h"


Chart::~Chart(){
}

Chart::Chart(){
    cX = 0;         // posizione x
    cY = 0;         // posizione y
    cW = 100;       // width
    cH = 100;       // height
    lX = cX+cW+20;  // legend x
    lY = cY;        // legend y
    pW = 0;
}

Chart::chartPiece::chartPiece(){}

void Chart::chartPiece::addName(QString name){
    pname = name;
}

void Chart::chartPiece::setColor(QColor color){
    rgbColor = color;
}
void Chart::chartPiece::setPerc(float Percentage){
    pPerc = Percentage;
}

void Chart::setCoordinates(double x, double y, double w, double h){
    this->cX = x;   // Posizione x all'interno del canvas contenitore
    this->cY = y;   // Posizione y all'interno del canvas contenitore
    this->cW = w;   // Width del chart
    this->cH = h;   // Height del chart
    // Legend coordinates
    this->lX = cX+cW+20;
    this->lY = cY;
}

void Chart::addPiece(QString name, QColor color, float Percentage){
    chartPiece piece;
    piece.addName(name);
    piece.setColor(color);
    piece.setPerc(Percentage);
    pieces.append(piece);
}
