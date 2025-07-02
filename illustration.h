#ifndef ILLUSTRATION_H
#define ILLUSTRATION_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QButtonGroup>
class illustration : public QWidget
{
    Q_OBJECT
public:
    explicit illustration(QWidget *parent = nullptr);
private:
    QWidget *parent;
    QPushButton *returnbtn;
    QWidget* leftWidget;
    QWidget* rightWidget;

    QVBoxLayout *rightLayout;
    QStackedWidget *stackedWidget;
    QButtonGroup *btnGroup;
    void initNav();
    void initMain();
public slots:
    void returnbtnclick();
    void buttonClicked();
};

#endif // ILLUSTRATION_H
