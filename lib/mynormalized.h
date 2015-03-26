#ifndef MYNORMALIZED_H
#define MYNORMALIZED_H
#include <QVector>
#include "mydata.h"
#include "./lib/myerror.h"

class myNormalized
{
public:
    myNormalized(myData*);
    double& atIndex(const int& i) throw (myError);
    int count() const;
private:
    QVector<double> _Data;
    void normalize(myData*);
};

#endif // MYNORMALIZED_H
