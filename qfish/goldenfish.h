#ifndef GOLDENFISH_H
#define GOLDENFISH_H
#include "qfish.h"
class goldenfish:public QFish
{
public:
    goldenfish(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp=1,int value=20);
    void advance(int phase);
};

#endif // GOLDENFISH_H
