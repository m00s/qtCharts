#include "gui/mymainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss("./stylesheet.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    myMainWindow w;
    w.show();
    // Decomment for expansion effect
    //w.showMaximized();
    return a.exec();
}
