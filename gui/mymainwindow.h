#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "./lib/myerror.h"
#include "chartsheet.h"

class myMainWindow : public QMainWindow
{
    Q_OBJECT
    QTabWidget* tab;
    QToolBar *toolbar;
    QToolBar *toolbarGraph;
    void loadToolBar();

public:
    myMainWindow(QWidget *parent = 0);
    ~myMainWindow();

private slots:
    void closeAll();
    void newSheet();
    void loadSheet();
    void saveSheet() throw (myError);
    void onCloseTab(int);

    void pieAction();
    void lineAction();
    void histoAction();
};

#endif // MYMAINWINDOW_H
