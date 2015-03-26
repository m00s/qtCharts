#include "myerror.h"
#include <QMessageBox>

myError::myError(QString s){
    QMessageBox::warning(0,"Error", s);
}
