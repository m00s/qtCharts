#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T12:23:21
#
#-------------------------------------------------

QT       += core xml gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Charts
TEMPLATE = app


SOURCES += main.cpp\
        gui/mymainwindow.cpp \
    lib/mydata.cpp \
    lib/myerror.cpp \
    lib/chart.cpp \
    lib/pieChart.cpp \
    gui/canvas.cpp \
    lib/mynormalized.cpp \
    lib/histogramm.cpp \
    lib/linechart.cpp \
    gui/chartsheet.cpp

HEADERS  += gui/mymainwindow.h \
    lib/mydata.h \
    lib/myerror.h \
    lib/chart.h \
    lib/pieChart.h \
    gui/canvas.h \
    lib/mynormalized.h \
    lib/histogramm.h \
    lib/linechart.h \
    gui/chartsheet.h

OTHER_FILES += \
    stylesheet.qss \
    istogramma.png \
    piechart.png \
    linechart.png
