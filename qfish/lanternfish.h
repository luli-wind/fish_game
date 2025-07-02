#ifndef LANTERNFISH_H
#define LANTERNFISH_H
#include "qfish.h"
class lanternfish:public QFish
{
public:
    lanternfish(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=15,int value=150);
     void advance(int phase);
};

#endif // LANTERNFISH_H
