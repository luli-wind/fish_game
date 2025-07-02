#include "qfish.h"
#include "../qpixmapitem/qcoin.h"


QFish::QFish(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp,int value):QPixmapItem(fileName,scene)
{


    this->hp=hp;
    this->maxhp=hp;
    this->value=value;
    this->isLeft = isLeft;
    int randomIntY = QRandomGenerator::global()->bounded(600);
    if(this->isLeft==1)
    {
        this->setPos(-130,100+randomIntY);
    }
    if(this->isLeft==-1)
     {
         this->setPos(1100,100+randomIntY);
     }


}

void QFish::advance(int phase)
{
    if (!phase) return;
    currentFrame = (currentFrame % 4) + 1;  // 更新帧索引
     if(this->mapToScene(0,0).y() <=-5 ||
        this->mapToScene(0,0).x()>=1024||
        this->mapToScene(0,0).x()<=-100||
        this->mapToScene(0,0).y()>=900)//超出边界后重新定义位置
     {
         int randomIntY = QRandomGenerator::global()->bounded(600);
         if(this->isLeft==1) //如果是左侧的鱼，刷新在左侧
         {
             this->setPos(-30,100+randomIntY);  //用随机数增加刷新点的随机性，让鱼分开出现
         }
         if(isLeft==-1) //如果是右侧的鱼，刷新在右侧
         {
             this->setPos(1000,100+randomIntY);
        }

      }
     int xspeed =  QRandomGenerator::global()->bounded(10);
     int yspeed =QRandomGenerator::global()->bounded(5);
     this->setPos(mapToScene(this->isLeft*xspeed,yspeed-3));//设置随机速度

}

 void QFish::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{

   const QPixmap &pixmap = (isLeft == 1) ? m_leftFrames[this->currentFrame - 1] :
                                             m_rightFrames[this->currentFrame - 1];

    painter->drawPixmap(-pixmap.width()/2, -pixmap.height(), pixmap);
}

 void QFish::fish_death()
{
     emit dead(this);
     QPointF fishPos= this->pos();


    QPointF targetPos=QPointF(180,740);

    QCoin* coin = new QCoin(":/image/coin1.png",this->scene(),fishPos,targetPos);

    coin->flyToTarget();

    this->deleteLater();

    // int randomIntY = QRandomGenerator::global()->bounded(600);
    // if(this->isLeft==1)
    // {
    //     this->setPos(-30,100+randomIntY);
    // }
    // if(this->isLeft==-1)
    // {
    //     this->setPos(1000,100+randomIntY);
    // }
    // this->hp = this->maxhp;
}



int QFish::getHp()
{
    return this->hp;
}

int QFish::getValue()
{
    return this->value;
}

void QFish::underAttack(int level)
{
    this->hp = this->hp-level;
}

QDebug operator<<(QDebug debug, const QFish* fish) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "QFish(";
    if(fish) {
        debug << fish->objectName()
        << ", pos=" << fish->pos();
    } else {
        debug << "nullptr";
    }
    debug << ')';
    return debug;
}
