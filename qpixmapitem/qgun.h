#ifndef QGUN_H
#define QGUN_H
#include <QGraphicsItem>
 #include <QPixmap>
#include <QPainter>
#include "qpixmapitem.h"
class QGun: public QPixmapItem
{
public:
    QGun(const QString & fileName,QGraphicsScene *scene);
    int getLevel();
    void setLevel(int level);
    void setGun(int level);
private:
    int level;

};

#endif // QGUN_H
