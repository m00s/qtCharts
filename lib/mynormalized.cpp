#include "mynormalized.h"

myNormalized::myNormalized(myData *d){
    normalize(d);
}

void myNormalized::normalize(myData *d){
    double sum = d->contentSum();

    for(int i=0; i<d->count(); i++){
        _Data.push_back(d->atIndex(i)*100/sum);
    }
}

double &myNormalized::atIndex(const int &i) throw (myError){
    if (i<0 || i>_Data.count())
        throw myError("in mynormalized.cpp: 'Index out of Range Exception'");
    else
        return _Data[i];
}

int myNormalized::count() const{
    return _Data.count();
}
