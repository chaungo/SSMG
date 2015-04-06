#include "graphics.h"
#include <math.h>
#include <QString>
#include <QList>
#include <QPainter>
#include <QApplication>
#include <iostream>
#include <string>
#include <QTextDocument>

graphics::graphics(QWidget *parent) :
    QWidget(parent)
{
    position =0;
    tam=0;
    tam1=0;
    tam2=1;
    tam3 = 1;
    timerId = startTimer(100);
    mode=0;
}

void graphics::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);
    position +=1;
    tam +=1;
    tam1 +=1;
    tam3 +=1;
    repaint();
}

void graphics::paintEvent(QPaintEvent *){
    QPainter ve(this);
    ve.setRenderHint(QPainter::Antialiasing);

    if(mode == 1) game(ve);
    if(mode == 2) danh(ve);
    if(mode == 3) thoat(ve);
}

void graphics::game(QPainter &painter)
{
    if (position < 100){


        int w = width();
        int h = height();
        QPixmap bautroi("/bautroi2.jpg");
        painter.drawPixmap(0,0,width(),height(),bautroi);
        QPixmap earth("/earth.png");
        painter.drawPixmap(w/2 - 100,h/2 - 100,200,200,earth);
        QPixmap nguoituyet("/snowman5.png");

        QPointF X(width()/2,height()/5);
        QPointF C(width()/2,height()/2);
        double x = X.x(),y=X.y();
        double Vx = C.x(),Vy = C.y();

        double x2 = X.x(),y2=X.y();
        double Vx2 = C.x(),Vy2 = C.y();
        double teta = (M_PI*position*10)/180;
        double teta2 = (M_PI*position*10+550)/180;

        double xphay=x*cos(teta)-y*sin(teta) + Vx*(1-cos(teta)) + Vy*sin(teta);
        double yphay=x*sin(teta)+y*cos(teta) - Vx*sin(teta)+Vy*(1-cos(teta));

        double xphay2 = x2*cos(teta2)-y2*sin(teta2) + Vx2*(1-cos(teta2)) + Vy2*sin(teta2);
        double yphay2 = x2*sin(teta2)+y2*cos(teta2) - Vx2*sin(teta2)+Vy2*(1-cos(teta2));

        x= xphay;
        y= yphay;
        x2 = xphay2;
        y2= yphay2;
        Vx = xphay;
        Vy=yphay;
        x = Vx - 80;
        y = Vy - 80;
        Vx2 = xphay2;
        Vy2=yphay2;
        x2 = Vx2 - 80;
        y2 = Vy2 - 80;
        painter.drawPixmap(xphay-40,yphay-40,80,80,nguoituyet);
        painter.drawPixmap(xphay2-40,yphay2-40,80,80,nguoituyet);
        if(position%10==0) vechu(painter,"Loading...",20,width()/2-50,height()-10);
        else vechu(painter,"Loading.",20,width()/2-50,height()-10);


    }
    else {
        QPixmap nha("/nha.jpg");
        QPixmap onggia("/onggia.png");
        QPixmap nguoituyet("/snowman5.png");
        painter.drawPixmap(width()-(position-100)*20,0,width(),height(),nha);
        if (position >= 162)
        {
            if(position==162) hddanh=false;

            painter.drawPixmap(0,0,width(),height(),nha);
            if (hddanh) {
                danh(painter);
            }
            else tam3=0;
            painter.drawPixmap(((width()-tam1*20*0.5*(diem+1))),height()/2+100,180,200,nguoituyet);
            painter.drawPixmap(width()-(tam-150)*20,0,(tam-150)*4,(tam-150)*2,onggia);
            if (tam==250) tam=150;
            if ((width()-tam1*20*0.5*(diem+1))<=0) {

                QPixmap thua("/gameover.jpg");
                painter.drawPixmap(0,0,width(),height(),thua);
                if (position % 2 == 0) painter.drawPixmap(-10,-10,width()+20,height()+20,thua);
                else painter.drawPixmap(0,0,width(),height(),thua);
                vechu(painter,"GAME OVER !!!",40, width()/2+150,300);
            }
            int quaX=(width()/2-tam3/2), quaY=(tam3*20-tam3/2);
            int Xmin=width()-tam1*20*0.5*(diem+1), Xmax=Xmin+180;
            int Ymin=height()/2+100, Ymax=height()/2+300;
            if ((quaX >= Xmin) && (quaX <= Xmax) && (quaY >= Ymin) && (quaY <= Ymax)){
                congdiem();
                tam1=0;
                tam3=0;
                hddanh=false;
            }
            QString sDiem= QString::number(diem);
            vechu(painter,"Điểm:"+sDiem,40,10,50);
        }
        else {
            tam1=0;
            tam2=1;
        }
    }

}


void graphics::danh(QPainter &ve){

    QPixmap danh("/qua.png");

    ve.drawPixmap(width()/2-tam3/2,tam3*20-tam3/2,70+tam3,50+tam3,danh);
}

void graphics::thoat(QPainter &){
    resetP();
    qApp->closeAllWindows();
}
void graphics::resetP(){
    position=0;
    tam=0;
    tam1=0;
    tam2=1;
    tam3=0;
    hddanh=false;
    diem=0;
}

void graphics::vechu(QPainter &painter, QString s, int cochu,int x,int y){
    QFont font=painter.font() ;
    font.setPointSize (cochu);
    font.setWeight(QFont::DemiBold);
    painter.setFont(font);
    if (position % 2 ==0)
        painter.setPen( Qt::red );
    else
        painter.setPen( Qt::black );
    QPoint point = QPoint(x,y);
    painter.drawText( point, s );
}

void graphics::congdiem(){
    diem=diem+1;
}


