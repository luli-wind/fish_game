#ifndef QCOIN_H
#define QCOIN_H
#include <QObject>

#include <QPoint>
#include "qpixmapitem.h"
#include <QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
class QCoin:public QObject,public QPixmapItem
{
    Q_OBJECT
     Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    QCoin(const QString & fileName,QGraphicsScene *scene,QPointF& startPos, const QPointF& targetPos);
    // 启动金币飞行动画
    void flyToTarget();
signals:
    void animationFinished(); // 动画完成信号

private slots:
    void onAnimationFinished();


private:
    QPropertyAnimation *m_posAnimation; // 位置动画
    QPropertyAnimation *m_scaleAnimation; // 缩放动画
    QPointF m_targetPos; // 目标位置（左下角方框中心）
};

#endif // QCOIN_H
