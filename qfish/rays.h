#ifndef RAYS_H
#define RAYS_H
#include "qfish.h"
class rays:public QFish
{
public:
    rays(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=20,int value=200);
    void advance(int phase);
};

#endif // RAYS_H
