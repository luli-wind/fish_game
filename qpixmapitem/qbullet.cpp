#include "qbullet.h"
#include "qnet.h"
QBullet::QBullet(const QString & fileName,QGraphicsScene *scene,qreal angle,int level):QPixmapItem(fileName,scene)
{
    this->scene=scene;
    qreal dx,dy;
    qreal rad;
    rad =angle*3.14159/180;
    dx=90*cos(rad);
    dy=90*sin(rad);
    this->level=level;
    this->setPos(scene->width()/2+dx,scene->height()-dy);
    this->setRotation(90-angle);
}

void QBullet::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->drawPixmap(-pixmap.width()/2,-pixmap.height(),pixmap);
    if(!this->collidingItems().empty())//碰撞检测
    {
        docolliding();
    }
}

void QBullet::advance(int phase)
{
    if(this->mapToScene(0,0).x()<=0 || this->mapToScene(0,0).x()>=1024 || this->mapToScene(0,0).y()<=0)
    {
        delete this;
    }

    else
    {
        this->setPos(mapToScene(0,-40));//设置子弹发射速度
    }
}


 void QBullet::docolliding()
{
     QString fileName;
     switch(level)
     {
     case 1:
         fileName=":/image/net1.png";
         break;
     case 2:
         fileName=":/image/net2.png";
         break;
     case 3:
         fileName=":/image/net3.png";
         break;
     case 4:
         fileName=":/image/net4.png";
         break;
     case 5:
         fileName=":/image/net5.png";
         break;
     case 6:
         fileName=":/image/net6.png";
         break;
     case 7:
         fileName=":/image/net7.png";
         break;
     }

     QNet *net = new QNet(fileName,scene,this->level);
    net->setPos(mapToScene(0,0));
     delete this;
}
