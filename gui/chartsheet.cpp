#include "chartsheet.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QToolBar>
#include <QToolTip>
#include "./lib/pieChart.h"
#include "./lib/histogramm.h"
#include "./lib/linechart.h"
#include "./lib/mynormalized.h"
#include <QLineEdit>
#include <QDoubleValidator>

chartSheet::chartSheet(QWidget *parent) :
    QMainWindow(parent), grid(new QTableWidget()), _Values(new myData()), colors(new QColor[MAXCOLORS]), validator(0, 9999, 5, grid){
    connect(grid, SIGNAL(cellChanged(int,int)), this, SLOT(validateCell(int,int)));
    setLayout();
    setColors();
}

chartSheet::chartSheet(QString s, QWidget *parent) :
    QMainWindow(parent), grid(new QTableWidget()), _Values(new myData(s)), colors(new QColor[MAXCOLORS]), validator(0, 9999, 5, grid){
    connect(grid, SIGNAL(cellChanged(int,int)), this, SLOT(validateCell(int,int)));
    setLayout();
    loadGrid();
    setColors();
}

chartSheet::~chartSheet(){
    // CHIAMATA MANUALE AI DISTRUTTORI DEI CANVAS
    QList<canvas*>::const_iterator it = canvasList.begin();
    for( ; it!=canvasList.end(); ++it)
        delete *it;
    delete _Values;
    delete colors;
    qDebug() << "Distruttore chartsSheet";
}

void chartSheet::setColors(){
    // init color array
    for ( int i=0; i<MAXCOLORS; i++ )
        colors[i] = QColor(rand()%255, rand()%255, rand()%255);
}

void chartSheet::loadPieces(Chart*& t){
    myNormalized* n = new myNormalized(_Values);
    for(int i=0; i<n->count(); i++){
        if(n->atIndex(i)!=0)
            t->addPiece("item" + QString::number(i+1), colors[rand() % MAXCOLORS], n->atIndex(i));
    }
    // ELIMINO IL myNormalized APPENA ALLOCATO?
    delete n;
}

void chartSheet::drawGraph(Chart *& t){
    loadPieces(t);
    canvasList.push_back(new canvas(_Values, t, this));
}

void chartSheet::loadDataFromGrid(){
    int r = grid->rowCount();
    int c = grid->columnCount();
    bool null = false;
    _Values->clear();
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(grid->item(i,j) != 0){
                if(grid->item(i,j)->text().toDouble() != 0)
                    _Values->push(grid->item(i,j)->text().toDouble());
                else{
                    null = TRUE;
                }
            }
        }
    }
    if(null){
        // SHOW TOOLTIP
        QRect tt(100, 100, 50, 20);
        QPoint p(500, 200);
        QToolTip::showText(p, QString("Gli zeri verranno ignorati"), new QWidget(), tt);
    }

}

void chartSheet::saveSheet2Xml(QString filename){
    loadDataFromGrid();
    if(_Values->count())
        _Values->writeXML(filename);
    else
        throw myError(QString("File vuoto\nSalvataggio fallito"));
}

void chartSheet::drawPie(){
    loadDataFromGrid();
    if(_Values->count()){
        Chart* t = new pieChart();
        drawGraph(t);
    }
}

void chartSheet::drawLine(){
    loadDataFromGrid();
    if(_Values->count()){
        Chart* t = new lineChart(_Values);
        drawGraph(t);
    }
}

void chartSheet::drawHisto(){
    loadDataFromGrid();
    if(_Values->count()){
        Chart* t = new histogramm(_Values);
        drawGraph(t);
    }
}

void chartSheet::removeCanvas(){
    canvas* s = static_cast<canvas*>(sender());
    canvasList.removeOne(s);
    s->deleteLater();
}

void chartSheet::validateCell(int i, int j){
    QString tmp = grid->item(i,j)->text();
    int a = 0;
    QValidator::State valid = validator.validate( *(const_cast<QString*> (&tmp)) , a);
    if(valid == QValidator::Invalid || grid->item(i,j)->text()==0){
        grid->item(i,j)->setText("");
    }
}

void chartSheet::setLayout(){
    grid->setRowCount(30);
    grid->setColumnCount(20);
    setCentralWidget(grid);
}

void chartSheet::loadGrid(){
    int row = grid->rowCount();
    int col = grid->columnCount();
    int k=0, j=0;
    for(int i=0; i<_Values->count(); i++){
        grid->setItem(k, j++, new QTableWidgetItem(QString::number(_Values->atIndex(i))));

        if(j==col+1){
            k++;
            j=0;
        }
        if(k==31){
            grid->insertRow(row);
        }
    }
}


