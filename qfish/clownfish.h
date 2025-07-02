#ifndef CLOWNFISH_H
#define CLOWNFISH_H
#include "qfish.h"
class clownFish:public QFish
{
public:
    clownFish(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=2,int value=30);
    void advance(int phase);
    };

#endif // CLOWNFISH_H
