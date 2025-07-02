#include "qcoin.h"

QCoin::QCoin(const QString & fileName,QGraphicsScene *scene,QPointF& startPos, const QPointF& targetPos):QObject(nullptr), QPixmapItem(fileName,scene)
{

    // 加载金币图片
    //setPixmap(QPixmap(fileName).scaled(30, 30, Qt::KeepAspectRatio));
    setPos(startPos); // 初始位置为鱼死亡的位置



    // 初始化位置动画
    m_posAnimation = new QPropertyAnimation(this, "pos", this);
    m_posAnimation->setDuration(1000); // 动画时长 1 秒
    m_posAnimation->setStartValue(startPos);
    m_posAnimation->setEndValue(targetPos);
    m_posAnimation->setEasingCurve(QEasingCurve::OutQuad); // 缓动曲线



    // 动画结束自动删除对象
    this->connect(m_posAnimation, &QPropertyAnimation::finished, this, &QCoin::onAnimationFinished);
}

void QCoin::flyToTarget() {

    m_posAnimation->start();

}


void QCoin::onAnimationFinished() {
    emit animationFinished();
    this->deleteLater(); // 动画完成后删除对象
}


