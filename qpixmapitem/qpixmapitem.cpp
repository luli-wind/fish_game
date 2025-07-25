#include "qpixmapitem.h"

QPixmapItem::QPixmapItem(const QString &fileName,QGraphicsScene *scene) {
    pixmap.load(fileName);
    scene->addItem(this);
}

QRectF QPixmapItem::boundingRect() const
{
    return QRectF(-pixmap.width()/2,-pixmap.height(),pixmap.width(),pixmap.height());
}
void QPixmapItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    painter->drawPixmap(-pixmap.width()/2,-pixmap.height(),pixmap);
}

