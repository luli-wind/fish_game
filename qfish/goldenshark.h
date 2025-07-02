#ifndef GOLDENSHARK_H
#define GOLDENSHARK_H
#include "qfish.h"
class goldenshark:public QFish
{
public:
    goldenshark(const QString & fileName,QGraphicsScene *scene,int isLeft=1,int hp=10,int value=500);
    void advance(int phase);
};

#endif // GOLDENSHARK_H
