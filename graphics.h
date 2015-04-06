#ifndef graphics_H
#define graphics_H

#include <QWidget>
#include <vector>

using namespace std;

class graphics : public QWidget
{
    Q_OBJECT
public:
    explicit graphics(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    int hang, vitri,position=0,timerId,h,w,mode,tam=0,tam1=0,diem=0,tam2=1, tam3;
    void game(QPainter &);
    void danh(QPainter &);
    void thoat(QPainter &);
    void resetP();
    bool hddanh = false;
    void vechu(QPainter &, QString s,int cochu,int x,int y);
    QString s;
    void congdiem();



signals:

public slots:

};

#endif // graphics_H

