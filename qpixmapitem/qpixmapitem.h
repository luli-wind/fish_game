#ifndef QPIXMAPITEM_H
#define QPIXMAPITEM_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
class QPixmapItem: public QGraphicsItem
{
public:
    QPixmapItem(const QString & fileName,QGraphicsScene *scene);
    virtual QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
protected:
    QPixmap pixmap;
};

#endif // QPIXMAPITEM_H
