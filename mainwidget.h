#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <Qicon>
#include <QBrush>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "easyview.h"
#include "illustration.h"
#include "shop.h"
#include <QMessageBox>

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();
private:
    QLabel *label;
    QPushButton *startbtn;
    QPushButton *illustrationbtn;
    QPushButton *shopbtn;
    QPushButton *quitbtn;
    QVBoxLayout *vboxlayout;
    illustration  *illustration;
    EasyView *easyview;
    shop* shop;

public slots:
    void startbtnclick();//槽函数
    void quitbtnclick();
    void illustrationbtnclick();
    void shopbtnclick();
};
#endif // MAINWIDGET_H
