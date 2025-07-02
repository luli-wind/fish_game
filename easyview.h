#ifndef EASYVIEW_H
#define EASYVIEW_H
#include <QGraphicsView>
#include <Qicon>
#include <QBrush>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QTimer>
#include <QPoint>
#include <QLine>
#include <QLineF>
#include <QSharedPointer>
#include "qpixmapitem/qgun.h"
#include "qfish/qfish.h"
#include "qpixmapitem/qcoincounter.h"
#include "cannonmanager.h"
class EasyView:public QGraphicsView
{
     Q_OBJECT
public:
    EasyView(QWidget *parent = nullptr);
    ~EasyView();
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void generateFish();
    void drawBackground(QPainter *painter, const QRectF &rect);
    void showPurchasePrompt(int level);
    void spawnFishGroup(int count);  // 生成鱼群函数
private:

    QPushButton *returnbtn;
    QPushButton *uplevelbtn;
    QPushButton *downlevelbtn;
    QGraphicsScene *scene;
    QGun *gun;

    QTimer *timer;
    QWidget *parent;
    qint64 m_lastTriggerTime; // 新增成员变量
    QPixmap backgroundImage;
    QCoinCounter* coinCounter;
    CannonManager* cannonmanager;

    QList<QSharedPointer<QFish>> fishes;

    // 游戏参数
    const int MIN_FISH_COUNT = 3;    // 鱼的最小数量阈值
    const int GROUP_SIZE = 5;        // 每次生成的鱼群大小
    int currentFishCount = 0;        // 当前存活的鱼数量
signals:
    void fired(int level);

public slots:
    void returnbtnclick();
    void uplevelbtnclick();
    void downlevelbtnclick();
    //void handleFishDeath(QSharedPointer<QFish> deadFish);  // 死亡处理函数
};

#endif // EASYVIEW_H
