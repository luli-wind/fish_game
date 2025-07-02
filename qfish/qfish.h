#ifndef QFISH_H
#define QFISH_H
#include <QRandomGenerator>
#include "../qpixmapitem/qpixmapitem.h"
#include <QObject>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>
class QFish; // 前向声明

QDebug operator<<(QDebug debug, const QFish* fish);
class QFish:public QObject,public QPixmapItem
{
     Q_OBJECT
public:
    QFish(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp,int value);
    void advance(int phase);
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    void fish_death();
    int getHp();
    int getValue();
    void underAttack(int level);//被渔网碰到后会掉血

protected:
    int hp;//当前生命值
    int maxhp;//最大生命值
    int value;//鱼的价值
    int isLeft;//判断是否出现再左边
    int  currentFrame;
    QVector<QPixmap> m_leftFrames;
    QVector<QPixmap> m_rightFrames;
signals:
    void dead(QFish* fish);
};

#endif // QFISH_H
