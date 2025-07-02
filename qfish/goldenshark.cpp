#include "goldenshark.h"

goldenshark::goldenshark(const QString & fileName,QGraphicsScene *scene,int isLeft,int hp,int value):QFish(fileName,scene,isLeft,hp,value)
{
    // 初始化时加载所有帧
    for (int i = 1; i <= 8; ++i) {
        m_leftFrames << QPixmap(QString(":/image/goldenshark%1.png").arg(i));

    }
    this->currentFrame=1;
}
void goldenshark::advance(int phase)
{
    if (!phase) return;
    currentFrame = (currentFrame % 8) + 1;  // 更新帧索引
    if(this->mapToScene(0,0).y() <=-5 ||
        this->mapToScene(0,0).x()>=1124||
        this->mapToScene(0,0).x()<=-500||
        this->mapToScene(0,0).y()>=900)//超出边界后重新定义位置
    {
        int randomIntY = QRandomGenerator::global()->bounded(600);
        if(this->isLeft==1) //如果是左侧的鱼，刷新在左侧
        {
            this->setPos(-330,100+randomIntY);  //用随机数增加刷新点的随机性，让鱼分开出现
        }
        if(isLeft==-1) //如果是右侧的鱼，刷新在右侧
        {
            this->setPos(1200,100+randomIntY);
        }

    }
    int xspeed =  QRandomGenerator::global()->bounded(20)+8;

    this->setPos(mapToScene(this->isLeft*xspeed,0));//设置随机速度
}
