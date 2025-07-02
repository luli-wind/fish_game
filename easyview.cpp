#include "easyview.h"
#include "qpixmapitem/qbullet.h"
#include "qfish/clownfish.h"
#include "qfish/goldenfish.h"
#include "qfish/turtle.h"
#include "qfish/rays.h"
#include "qfish/lanternfish.h"
#include "qfish/pufferfish.h"
#include "qfish/shark.h"
#include "qfish/goldenshark.h"
#include <QDateTime>
#include <QMessageBox>
#include <QPointer>
EasyView::EasyView(QWidget *parent) {
    this->parent=parent;
    this->setFixedSize(1024,768);//设置窗口大小
    this->setWindowTitle("捕鱼达人");//设置窗口标题
    this->setWindowIcon(QIcon(":/image/icon.png"));//设置窗口图标
    this->setBackgroundBrush(QBrush(QPixmap(":/image/gamebg.jpg")));
    this->m_lastTriggerTime=0;
    this->setMouseTracking(true);

    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,this->width()-2,this->height()-2);
    this->setScene(scene);

    backgroundImage.load(":/image/bottom-bar.png");

    QString buttonStyle =
        "QPushButton {"
        "    background-color: rgba(0, 0, 0, 0.3);"
        "    border: 2px solid #1E90FF;"
        "    color: white;"
        "    padding: 8px 16px;"
        "    border-radius: 5px;"
        "    font-size: 14px;"

        "}"
        "QPushButton:hover {"
        "    border: 2px solid #00BFFF;"
        "}"
        "QPushButton:pressed {"
        "    background-color: rgba(30, 144, 255, 50);"
        "}";
    this->returnbtn=new QPushButton("返回",this);
    this->returnbtn->setStyleSheet(buttonStyle);
    returnbtn->move(this->width()-80,this->height()-50);//设置按钮位置


    this->uplevelbtn=new QPushButton(this);
    this->uplevelbtn->move(this->width()/2+45,this->height()-30);
    this->uplevelbtn->setFixedSize(45,25);
    this->uplevelbtn->setStyleSheet(
        "QPushButton { border-image: url(:/image/uplevel.png); }"
        "QPushButton:pressed { border-image: url(:/image/uplevel_down.png); }"
        );

    this->downlevelbtn=new QPushButton(this);
    this->downlevelbtn->move(this->width()/2-80,this->height()-30);
    this->downlevelbtn->setFixedSize(45,25);
    this->downlevelbtn->setStyleSheet(
        "QPushButton { border-image: url(:/image/downlevel.png); }"
        "QPushButton:pressed { border-image: url(:/image/downlevel_down.png); }"
        );


    //大炮
    gun = new QGun(":/image/gun1.png",scene);
    gun->setPos(this->width()/2,this->height());

    //鱼
    int left=1;
    int right=-1;

    fishes.append(QSharedPointer<QFish>(new clownFish(":/image/clownfish1.png", scene, left)));

    fishes.append(QSharedPointer<QFish>(new clownFish(":/image/clownfish1.png", scene, left)));

    fishes.append(QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1.png",scene,left)));
    fishes.append(QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1right.png",scene,right)));

    fishes.append(QSharedPointer<QFish>(new turtle(":/image/turtle1.png",scene,left)));

    fishes.append(QSharedPointer<QFish>(new rays(":/image/rays1.png",scene,left)));

    fishes.append(QSharedPointer<QFish>(new lanternfish(":/image/lanternfish1.png",scene,left)));


    fishes.append(QSharedPointer<QFish>(new pufferfish(":/image/pufferfish1right.png",scene,right)));

    fishes.append(QSharedPointer<QFish>(new shark(":/image/shark1right.png",scene,right)));


    fishes.append(QSharedPointer<QFish>(new goldenshark(":/image/goldenshark1.png",scene)));
    currentFishCount =fishes.size();



    QCoinCounter* coinCounter = new QCoinCounter();
    coinCounter->setPos(108, 737); // 设置显示位置（与你的金币箱UI对齐）
    scene->addItem(coinCounter);

    cannonmanager = CannonManager::instance();

    //定时器
    timer =new QTimer;

    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(166);

    this->connect(returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnclick()));
    this->connect(uplevelbtn,SIGNAL(clicked()),this,SLOT(uplevelbtnclick()));
    this->connect(downlevelbtn,SIGNAL(clicked()),this,SLOT(downlevelbtnclick()));

    for (auto& fish : fishes) {
         connect(fish.data(), &QFish::dead, this, [coinCounter,this](QFish* fish) {
            if (coinCounter && fish) {
                 currentFishCount--;
                coinCounter->add(fish->getValue());
                }
            if(currentFishCount<=MIN_FISH_COUNT)
            {
                    spawnFishGroup(GROUP_SIZE);
            }
            });
    }//捕鱼后，增加金币

    this->connect(this, &EasyView::fired, this,[coinCounter](int level) {
        coinCounter->subtract(level);
    });//发射炮弹消耗金币
}

void EasyView::resizeEvent(QResizeEvent *event)
{
    this->setBackgroundBrush(QBrush(QPixmap(":/image/gamebg.jpg").scaled(event->size())));

}

void EasyView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p;
    p=event->pos();
    //画线
    QLine line(this->width()/2,this->height(),p.x(),p.y());
    QLineF linef(line);
    gun->setRotation(-(linef.angle()-90));
}
void EasyView::mousePressEvent(QMouseEvent *event)
{

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    if(now - m_lastTriggerTime < 500) return;
    m_lastTriggerTime = now;
     emit fired(this->gun->getLevel());
    QPoint p;
    p=event->pos();
    //画线
    QLine line(this->width()/2,this->height(),p.x(),p.y());
    QLineF linef(line);
    //子弹的图画
    QString fileName;
    switch(this->gun->getLevel())
    {
    case 1:
        fileName=":/image/bullet1.png";
        break;
    case 2:
        fileName=":/image/bullet2.png";
        break;
    case 3:
        fileName=":/image/bullet3.png";
        break;
    case 4:
        fileName=":/image/bullet4.png";
        break;
    case 5:
        fileName=":/image/bullet5.png";
        break;
    case 6:
        fileName=":/image/bullet6.png";
        break;
    case 7:
        fileName=":/image/bullet7.png";
        break;
    }
    QBullet *bullet =new QBullet(fileName,scene,linef.angle(),this->gun->getLevel());
}

void EasyView::returnbtnclick()
{
    this->close();
    this->parent->show();
}

void EasyView::uplevelbtnclick()
{

    int nextLevel = gun->getLevel() + 1;
    if(nextLevel==8)
    {
        gun->setLevel(1);
        gun->setGun(1);
        return;
    }

    if (cannonmanager->hasLevel(nextLevel)) {
        gun->setLevel(nextLevel);
        gun->setGun(nextLevel);
    } else {
        showPurchasePrompt(nextLevel);
    }

}




void EasyView::downlevelbtnclick(){
    int nextLevel = gun->getLevel() -1;
    if(nextLevel==0)
    {
        if(cannonmanager->hasLevel(7))
        {
            gun->setLevel(7);
            gun->setGun(7);
            return;
        }
        else
        {
             showPurchasePrompt(nextLevel);
            return;
        }

    }

    if (cannonmanager->hasLevel(nextLevel)) {
        gun->setLevel(nextLevel);
        gun->setGun(nextLevel);
    } else {
       showPurchasePrompt(nextLevel);
    }
}



void EasyView::showPurchasePrompt(int level) {
    QMessageBox::StandardButton reply = QMessageBox::critical(
        this,                                   // 父窗口
        tr("升级失败!!!"),                         // 标题（支持国际化）
        tr("你没有对应等级的大炮，请前往商店购买!")              // 提示信息
        );


}

void EasyView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);
    qreal sceneWidth = scene->width();
    qreal sceneHeight = scene->height();

    qreal imageY = sceneHeight - backgroundImage.height(); // 图片底部对齐场景底部
    qreal imageX = (sceneWidth - backgroundImage.width()) / 2-40; // 水平居中

    painter->drawPixmap(QPointF(imageX, imageY), backgroundImage);
}





void EasyView::spawnFishGroup(int count) {
    int left = 1;
    int right = -1;

    for (int i = 0; i < count; i++) {


        // 随机创建不同类型的鱼
        int fishType = rand() % 8;
        QSharedPointer<QFish> fish=nullptr;

        switch (fishType) {
        case 0:
            fish = QSharedPointer<QFish>(new clownFish(":/image/clownfish1.png", scene, left));
            break;
        case 1:
            fish = QSharedPointer<QFish>(new clownFish(":/image/clownfish1right.png", scene, right));
            break;
        case 2:
            fish = QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1.png", scene, left));
            break;
        case 3:
            fish = QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1.png", scene, left));
            break;
        case 4:
            fish = QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1.png", scene, left));
            break;
        case 5:
            fish = QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1.png", scene, left));
            break;
        case 6:
            fish = QSharedPointer<QFish>(new goldenfish(":/image/goldenfish1.png", scene, left));
            break;

        case 7:
            fish = QSharedPointer<QFish>(new goldenshark(":/image/goldenshark1.png", scene,left));
            break;
        }


            fishes.append(fish);
            currentFishCount++;

            // // 连接死亡信号 (关键修复)
            // connect(fish.data(), &QFish::dead, this,
            //         [this, fish]() {  // 使用值捕获确保对象存活
            //             QPointer<EasyView> guard(this); // 添加安全守卫
            //             if (guard) {
            //                 handleFishDeath(fish);
            //             }
            //         },
            //         Qt::QueuedConnection); // 使用队列连接确保线程安全


}


}
// void EasyView::handleFishDeath(QSharedPointer<QFish> deadFish) {


//     // 增加金币
//     coinCounter->add(deadFish->getValue());



//     // 减少当前鱼数量
//     currentFishCount--;

//     // 检查是否需要生成新的鱼群
//     if (currentFishCount <= MIN_FISH_COUNT) {
//         spawnFishGroup(GROUP_SIZE);
//     }
// }


EasyView::~EasyView() {
    // 清理鱼群 - 智能指针会自动释放内存
    for (auto& fish : fishes) {
        fish->disconnect();  // 断开信号连接
    }
    fishes.clear();
}
