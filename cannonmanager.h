#ifndef CANNONMANAGER_H
#define CANNONMANAGER_H

#include <QObject>

class CannonManager: public QObject
{
     Q_OBJECT
public:
    CannonManager();
    static CannonManager* instance();
    void loadPurchasedLevels();
    bool hasLevel(int level) const;
    void purchaseLevel(int level);

signals:
    void levelPurchased(int level); // 购买成功信号

private:
    QList<int> purchasedLevels;

};

#endif // CANNONMANAGER_H
