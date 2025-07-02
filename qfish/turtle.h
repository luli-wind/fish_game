#ifndef TURTLE_H
#define TURTLE_H
#include "qfish.h"
class turtle:public QFish
{
public:
    turtle(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=12,int value=80);
    void advance(int phase);

};

#endif // TURTLE_H
