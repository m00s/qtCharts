#include "pieChart.h"

pieChart::pieChart() : Chart(), palpha(0){
}

pieChart::~pieChart(){
    //pieces.clear();
}

void pieChart::draw(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    pW = 0;
    double pdegree = 0;

    //Options
    QLinearGradient gradient(cX+0.5*cW,cY,cX+0.5*cW,cY+cH*2.5);
    gradient.setColorAt(1,Qt::black);    
  
    double sumangle = 0;
    for (int i=0;i<pieces.size();i++){
        sumangle += 3.6*pieces[i].pPerc;
    }
    painter->setBrush(Qt::darkGray);
    painter->drawPie(cX,cY+pW+5,cW,cH,palpha*16,sumangle*16);
    QPen pen;
    pen.setWidth(2);
    
    for (int i=0;i<pieces.size();i++){
		gradient.setColorAt(0,pieces[i].rgbColor);
	    painter->setBrush(gradient);
	    pen.setColor(pieces[i].rgbColor);
	    painter->setPen(pen);
	    pdegree = 3.6*pieces[i].pPerc;   
	    painter->drawPie(cX,cY,cW,cH,palpha*16,pdegree*16);
	    palpha += pdegree;
    }
}


void pieChart::drawLegend(QPainter *painter)
{
    double angle = palpha;
    painter->setPen(Qt::SolidLine);
	for (int i=pieces.size()-1;i>=0;i--){
        float len = 100;
        double pdegree = 3.6*pieces[i].pPerc;
        angle -= pdegree/2;
        QPointF p = getPnt(angle);
        QPointF p_ = getPnt(angle, cW+len,cH+len);
        int q = getQtr(angle);
        if (q == 3 || q == 4)
        {
            p.setY(p.y()+pW/2);
            p_.setY(p_.y()+pW/2);
        }
        painter->drawLine(p.x(),p.y(),p_.x(),p_.y());
        QString label = pieces[i].pname + " - " + QString("%L1").arg(pieces[i].pPerc,0,'f',1) +"%";
        float recW = painter->fontMetrics().width(label)+10;
        float recH = painter->fontMetrics().height()+10;
        p_.setX(p_.x()-recW/2 + recW/2*cos(angle*M_PI/180));
        p_.setY(p_.y()+recH/2 + recH/2*sin(angle*M_PI/180));
        painter->setBrush(Qt::white);
        painter->drawRoundRect(p_.x() ,p_.y(), recW, -recH);
        painter->drawText(p_.x()+5, p_.y()-recH/2+5, label);
        angle -= pdegree/2;
     }
}    


QPointF pieChart::getPnt(double angle, double R1, double R2){
    if (R1 == 0 && R2 == 0){
        R1 = cW;
        R2 = cH;
    }
    QPointF point;
    double x = R1/2*cos(angle*M_PI/180);
    x+=cW/2+cX;
    double y = -R2/2*sin(angle*M_PI/180);
    y+=cH/2+cY;
    point.setX(x);
    point.setY(y);
    return point;
}

int pieChart::getQtr(double angle){
    angle = Angle360(angle);
    if(angle>=0 && angle<90)
        return 1;
    if(angle>=90 && angle<180)
        return 2;
    if(angle>=180 && angle<270)
        return 3;
    else // angle>=270 && angle<360
        return 4;
}

double pieChart::Angle360(double angle){
    int i = (int)angle;
    double delta = angle - i;
    return (i%360 + delta);
}

















