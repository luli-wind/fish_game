#include "illustration.h"
#include "fish_illustration/clownfish_illustration.h"
#include "fish_illustration/goldenfish_illustration.h"
#include "fish_illustration/pufferfish_illustration.h"
#include "fish_illustration/turtle_illustration.h"
#include "fish_illustration/rays_illustration.h"
#include "fish_illustration/lanternfish_illustration.h"
#include "fish_illustration/shark_illustration.h"
#include "fish_illustration/goldenshark_illustration.h"
#include <QToolButton>

illustration::illustration(QWidget *parent)
    : QWidget{parent}
{
    this->parent=parent;
    this->setFixedSize(1024, 768);  // 同时设置最小和最大尺寸
    this->setWindowTitle("捕鱼达人");//设置窗口标题
    this->setWindowIcon(QIcon(":/image/icon.png"));//设置窗口图标

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

    QHBoxLayout* mainLayout=new QHBoxLayout(this);//水平布局
    mainLayout ->setSpacing(0);//间距
    mainLayout->setContentsMargins(0,0,0,0);


    //左侧窗体
    leftWidget =new QWidget(this);
    leftWidget->setObjectName("leftWidget");
    leftWidget ->setStyleSheet("#leftWidget{"
                              "background-color:rgb(220,240,255);"
                              "border-right:1px solid #c0dcf2;"
                              "}"
                              );

    QGridLayout* gridLayout=new QGridLayout(leftWidget);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(8,16,8,8);

    mainLayout->addWidget(leftWidget);

    //右侧窗口
    rightWidget = new QWidget(this);
    rightLayout =new QVBoxLayout(rightWidget);
    rightLayout ->setSpacing(0);//间距
    rightLayout->setContentsMargins(0,0,0,0);

    stackedWidget=new QStackedWidget(rightWidget);

    rightWidget->setObjectName("rightWidget");
    rightWidget ->setStyleSheet("#rightWidget{"
                              "background-color:rgb(235,245,255);"
                              "}"
                              );

    rightLayout->addWidget(stackedWidget);
    rightLayout->addWidget(returnbtn,0,Qt::AlignRight | Qt::AlignBottom);
    mainLayout->addWidget(rightWidget);

    this->connect(returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnclick()));

    initNav();
    initMain();
}

void illustration::initNav()
{
    //图鉴名称集合
    QStringList names;
    names<<"小丑鱼"
         <<"小金鱼"
         <<"河豚"
         <<"海龟"
         <<"魔鬼鱼"
         <<"灯笼鱼"
         <<"鲨鱼"
         <<"黄金鲨鱼";



    QString icons[] = {":/image/clownfish1.png",":/image/goldenfish1.png",":/image/pufferfish1.png",":/image/turtle1.png",
                        ":/image/rays1.png",":/image/lanternfish1.png",":/image/shark1.png",":/image/goldenshark1.png"};
    btnGroup = new QButtonGroup(this);
    for(int i=0;i<names.count();i++)
    {
        QToolButton* btn = new QToolButton();
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

        //设置文字
        btn->setText(QString("%1").arg(names.at(i)));

        //设置图标
        QPixmap pix =QPixmap(icons[i]);
        btn->setIcon(QIcon(pix));
        btn->setIconSize(QSize(80,80));

        //设置按钮可选中--按下类似复选框的功能
        btn->setCheckable(true);
        //设置按钮的样式
        btn->setStyleSheet(R"(
            QToolButton{
                border-style:none;
                border:1px solid #C0DCF2;
                font:18px "Microsoft YaHei";
                color:#386487;
                padding:5px;
                border-radius:5px;
                background:#DEF0FE;
            }
            QToolButton:hover{
                background:#C0DEF5;
            }
            QToolButton:checked{
                background:#C0DEF5;
            }
         )");
        //将按钮添加到btnGroup
        btnGroup->addButton(btn,i);

        //关联信号槽
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(buttonClicked()));
        QGridLayout* leftLayout=(QGridLayout*)leftWidget->layout();
        leftLayout->addWidget(btn,i/2,i%2);
    }
    //默认选中第一项
    btnGroup->button(0)->click();
}

void illustration::initMain()
{
    stackedWidget->addWidget(new clownfish_illustration());
    stackedWidget->addWidget(new goldenfish_illustration());
    stackedWidget->addWidget(new pufferfish_illustration());
    stackedWidget->addWidget(new turtle_illustration());
    stackedWidget->addWidget(new rays_illustration());
    stackedWidget->addWidget(new lanternfish_illustration());
    stackedWidget->addWidget(new shark_illustration());
    stackedWidget->addWidget(new goldenshark_illustration());
}

void illustration::returnbtnclick()
{
    this->close();

}

 void illustration::buttonClicked()
{
     stackedWidget->setCurrentIndex(btnGroup->checkedId());
}
