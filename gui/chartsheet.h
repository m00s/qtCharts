#ifndef CHARTSSHEET_H
#define CHARTSSHEET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QList>
#include "./lib/mydata.h"
#include "canvas.h"

class chartSheet : public QMainWindow
{
    Q_OBJECT
    void setLayout();
    void loadGrid();
    void loadDataFromGrid();
    void setColors();
    void loadPieces(Chart *&);
    void drawGraph(Chart *&);
    QTableWidget* grid;
    QList<canvas*> canvasList;
    myData* _Values;
    QColor* colors;
    QDoubleValidator validator;
public:
    explicit chartSheet(QWidget *parent = 0);
    explicit chartSheet(QString s, QWidget *parent = 0);
    ~chartSheet();
    void saveSheet2Xml(QString);
    void drawPie();
    void drawLine();
    void drawHisto();
signals:

public slots:
    void removeCanvas();
    void validateCell(int, int);
private slots:
};

#endif // CHARTSSHEET_H
