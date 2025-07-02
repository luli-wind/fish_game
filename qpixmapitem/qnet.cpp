#include "qnet.h"
#include "../qfish/qfish.h"
QNet::QNet(const QString & fileName,QGraphicsScene *scene,int level):QPixmapItem(fileName,scene)
{
    this->level=level;
}

void QNet::advance(int phase)
{
    if(!this->collidingItems().empty())//碰撞检测，碰到渔网的鱼会被抓住
    {
        QList<QGraphicsItem *> list=this->collidingItems();
        QList<QGraphicsItem *>::Iterator i;//定义迭代器，遍历链表
        QFish * fish;
        i = list.begin();
        while(i!=list.end())
        {
            fish=(QFish*)(*i);
            fish->underAttack(this->level);
            if(fish->getHp()<=0)
            {
                fish->fish_death();
            }

            i++;
        }
    }
    this->hide();
    delete this;

}
