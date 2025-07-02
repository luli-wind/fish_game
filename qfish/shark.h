#ifndef SHARK_H
#define SHARK_H
#include "qfish.h"
class shark:public QFish
{
public:
    shark(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=25,int value=300);
    void advance(int phase);
};

#endif // SHARK_H
