#include "qgun.h"

QGun::QGun(const QString & fileName,QGraphicsScene *scene):QPixmapItem(fileName,scene)
{
    this->level=1;
}


int QGun::getLevel()
{
    return level;
}

void QGun::setLevel(int level)
{
    this->level=level;
}

void QGun::setGun(int level)
{
    QString fileName;
    switch(level)
    {
    case 1:
        fileName=":/image/gun1.png";
        break;
    case 2:
        fileName=":/image/gun2.png";
        break;
    case 3:
        fileName=":/image/gun3.png";
        break;
    case 4:
        fileName=":/image/gun4.png";
        break;
    case 5:
        fileName=":/image/gun5.png";
        break;
    case 6:
        fileName=":/image/gun6.png";
        break;
    case 7:
        fileName=":/image/gun7.png";
        break;
    }

    pixmap.load(fileName);
}


