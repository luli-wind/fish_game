#ifndef QNET_H
#define QNET_H
#include "qpixmapitem.h"

class QNet:public QPixmapItem
{
public:
    QNet(const QString & fileName,QGraphicsScene *scene,int level);
    void advance(int phase);
private:
    int level;
};

#endif // QNET_H
