#include "mymainwindow.h"
#include <QTabWidget>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QString>
#include <QAction>
#include <QDebug>
#include "./lib/myerror.h"

myMainWindow::myMainWindow(QWidget *parent)
    : QMainWindow(parent), tab(new QTabWidget()), toolbar(new QToolBar()), toolbarGraph(new QToolBar()){
    loadToolBar();
    showMaximized();
    setCentralWidget(tab);
    tab->setTabsClosable(true);
    tab->addTab(new chartSheet(), QString("unsaved"));
    tab->setMovable(true);
    connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab(int)) );
}

myMainWindow::~myMainWindow(){
    delete toolbar;
    delete toolbarGraph;
    delete tab;
    qDebug() << "Distruttore myMainWindow";
}

void myMainWindow::loadToolBar(){
    //TOOLBAR FILE
    QPixmap newpix("new.png");
    QPixmap openpix("open.png");
    QPixmap savepix("save.png");
    QPixmap quitpix(QString("quit.png"));
    toolbar = addToolBar("main toolbar");
    QAction *newS = toolbar->addAction(QIcon(newpix), "&New File");
    connect(newS, SIGNAL(triggered()), this, SLOT(newSheet()));
    QAction *loadS = toolbar->addAction(QIcon(openpix), "Open File");
    connect(loadS, SIGNAL(triggered()), this, SLOT(loadSheet()));
    QAction *saveS = toolbar->addAction(QIcon(savepix), "Save File");
    connect(saveS, SIGNAL(triggered()), this, SLOT(saveSheet()));
    toolbar->addSeparator();
    QAction *quit = toolbar->addAction(QIcon(quitpix),"Quit");
    connect(quit, SIGNAL(triggered()), this, SLOT(closeAll()));
    toolbar->setMovable(false);

    //TOOLBAR GRAPH
    QPixmap piepix(“./gui/images/PieChart.png");
    QPixmap dpiepix("./gui/images/linechart.png");
    QPixmap histopix("./gui/images/Charts v1.1/istogramma.png");

    toolbarGraph = addToolBar("Graph toolbar");
    QAction *pieG = toolbarGraph->addAction(QIcon(piepix), "Pie");
    connect(pieG, SIGNAL(triggered()), this, SLOT(pieAction()));

    QAction *lineG = toolbarGraph->addAction(QIcon(dpiepix), "Line");
    connect(lineG, SIGNAL(triggered()), this, SLOT(lineAction()));

    QAction *histoG = toolbarGraph->addAction(QIcon(histopix), "Histogramm");
    connect(histoG, SIGNAL(triggered()), this, SLOT(histoAction()));
    this->insertToolBarBreak(toolbarGraph);
}

void myMainWindow::closeAll(){
    close();
}

void myMainWindow::newSheet(){
    chartSheet* t = new chartSheet();
    tab->addTab(t, QString("unsaved"));
    tab->setCurrentWidget(t);
}

void myMainWindow::loadSheet()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open XML File"),"/home", tr("XML Files (*.xml)"));
    if(path!=0){
        try{
            chartSheet* p = new chartSheet(path);
            if(path!=""){
                QFileInfo fi(path);
                tab->addTab(p, fi.baseName());
                tab->setCurrentWidget(p);
            }
        }catch(myError){}
    }
}

void myMainWindow::onCloseTab(int index){
    switch(QMessageBox::question(
            this,
            tr("Charts"),
            tr("Are you sure you want to close?"),

            QMessageBox::Yes |
            QMessageBox::No ))
    {
    case QMessageBox::Yes:{
         chartSheet* p = static_cast<chartSheet*>(tab->widget(index));
         delete p;
         tab->removeTab(index);
    }
        break;
      default:
        break;
    }
}

void myMainWindow::pieAction(){
    chartSheet* c = static_cast<chartSheet*>(tab->currentWidget());
        if(c){
            c->drawPie();
        }
}

void myMainWindow::lineAction(){
    chartSheet* c = static_cast<chartSheet*>(tab->currentWidget());
        if(c){
            c->drawLine();
        }
}

void myMainWindow::histoAction(){
    chartSheet* c = static_cast<chartSheet*>(tab->currentWidget());
        if(c){
            c->drawHisto();
        }
}

void myMainWindow::saveSheet() throw (myError)
{
    QString filter="XML files (*.xml)";
    QString fileName=QFileDialog::getSaveFileName(this, tr("&Save As"), QDir::currentPath(),
    "XML files (*.xml)", &filter, QFileDialog:: DontUseNativeDialog);
    chartSheet* p = dynamic_cast<chartSheet*>(tab->currentWidget());
    if(p)
    {
        p->saveSheet2Xml(fileName);
        QFileInfo fi(fileName);
        tab->setTabText(tab->currentIndex(), fi.baseName());
    }
    else
        throw myError(QString("dynamic_cast BAD_CAST"));
}
