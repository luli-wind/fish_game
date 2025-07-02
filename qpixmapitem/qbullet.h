#ifndef QBULLET_H
#define QBULLET_H
#include "qpixmapitem.h"

class QBullet:public QPixmapItem
{
public:
    QBullet(const QString & fileName,QGraphicsScene *scene,qreal angle,int level);
    void advance(int phase);
    void docolliding();
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
private:
    QGraphicsScene *scene;
    int level;
};

#endif // QBULLET_H
