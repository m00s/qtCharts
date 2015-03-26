#include "mydata.h"
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtCore>


myData::myData(){
}

myData::myData(QString s){
    loadXML(s);
}

int myData::count() const{
    return _Data.count();
}

double &myData::atIndex(const int &i) throw(myError){
    if (i<0 || i>_Data.count())
        throw myError("in mydata.cpp: 'Index out of Range Exception'");
    else
        return _Data[i];
}

void myData::push(double x){
    _Data.push_back(x);
}

void myData::loadXML(QString path) throw(myError){
    QDomDocument doc;
    QFile db(path);
    if(!db.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw myError(QString("Opening error"));
    }
    else{
        if(!doc.setContent(&db)){
                db.close();
                throw myError(QString("Error in handling db file"));
            }
    }

    QDomElement root = doc.firstChildElement();
    QDomNodeList items = root.elementsByTagName("item");
    for(int i = 0; i<items.count(); i++)
    {
        QDomNode itemNode = items.at(i);
        if(itemNode.isElement())
        {
            QDomElement itemele = itemNode.toElement();
            _Data.push_back(itemele.attribute("val").toDouble());
        }
    }
    db.close();
}

void myData::writeXML(QString filename) throw(myError){
    QDomDocument doc;
    QDomElement root = doc.createElement("root");
    doc.appendChild(root);

    for(int i=0; i<_Data.count(); i++)
    {
        QDomElement node = doc.createElement("item");
        node.setAttribute("val", QString::number(_Data[i]));
        root.appendChild(node);
    }

    QFile f(filename);
    if(!f.open( QIODevice::WriteOnly | QIODevice::Text))
        throw myError("Failed to open file" + QString(filename));
    else
    {
        QTextStream stream(&f);
        stream << doc.toString();
        f.close();
    }
}

double myData::contentSum() const{
    double sum = 0;
    QVector<double>::const_iterator it = _Data.begin();
    for( ; it!=_Data.end(); ++it){
        sum+=(*it);
    }
    return sum;
}

void myData::clear(){
    _Data.clear();
}






