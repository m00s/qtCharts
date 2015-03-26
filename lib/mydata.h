#ifndef MYDATA_H
#define MYDATA_H

#include <QVector>
#include "./lib/myerror.h"

class myData {
public:
    myData();
    myData(QString);
    int count() const;
    double& atIndex(const int& i) throw(myError);
    void push(double);
    void writeXML(QString) throw(myError);
    double contentSum() const;
    void clear();
private:
    QVector<double> _Data;
    void loadXML(QString) throw(myError);
};

#endif // MYDATA_H
