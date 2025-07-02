#ifndef PUFFERFISH_H
#define PUFFERFISH_H
#include "qfish.h"
class pufferfish:public QFish
{
public:
    pufferfish(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=10,int value=80);
    void advance(int phase);
};

#endif // PUFFERFISH_H
