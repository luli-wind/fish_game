#include "turtle.h"

turtle::turtle(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp,int value):QFish(fileName,scene,isLeft,hp,value)
{
    // 初始化时加载所有帧
    for (int i = 1; i <= 10; ++i) {
        m_leftFrames << QPixmap(QString(":/image/turtle%1.png").arg(i));
        m_rightFrames << QPixmap(QString(":/image/turtle%1right.png").arg(i));
    }
    this->currentFrame=1;

}

void turtle::advance(int phase)
{
    if (!phase) return;
    currentFrame = (currentFrame % 6) + 1;  // 更新帧索引
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
    int xspeed =  QRandomGenerator::global()->bounded(10)+3;

    this->setPos(mapToScene(this->isLeft*xspeed,0));//设置随机速度
}
