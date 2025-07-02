#ifndef SHOP_H
#define SHOP_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "qpixmapitem/qcoincounter.h"
class shop: public QWidget
{
    Q_OBJECT
public:
    shop(QWidget *parent = nullptr);
private:
    struct Product {
        QString name;
        int price;
        bool purchased;
        QPushButton* btn;
    };
    int coins;
    QList<Product> products;
    QLabel* coinLabel;
    QWidget *parent;
    QPushButton *returnbtn;
    void initProducts();
    QScrollArea* productArea;
    QVBoxLayout* productLayout;
    QHBoxLayout* bottomLayout;

    QCoinCounter* coinCounter;//金币计数

    void setCoinValue(int value);
public slots:
    void returnbtnclick();
};

#endif // SHOP_H
