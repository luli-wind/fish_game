#include "mainwidget.h"
mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    //this->resize(1024,768);//设置窗口大小
    this->setFixedSize(1024, 768);  // 同时设置最小和最大尺寸
    this->setWindowTitle("捕鱼达人");//设置窗口标题
    this->setWindowIcon(QIcon(":/image/icon.png"));//设置窗口图标

    QPalette palette;
    QPixmap background(":/image/startbg.jpg"); // 1. 加载图片（通过资源路径）
    palette.setBrush(QPalette::Window,background);// 2. 创建 QPalette 并设置画刷
    this->setPalette(palette);// 3. 应用调色板到窗口
    this->setAutoFillBackground(true);// 4. 确保窗口自动填充背景（关键！）

    //标签初始化
    this->label=new QLabel(this);
    QPixmap title(":/image/title.png");
    QPixmap scaledByFactor = title.scaled(title.size() * 0.3, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(scaledByFactor);

    //添加按钮
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

    this->startbtn=new QPushButton("开始游戏",this);
    this->startbtn->setStyleSheet(buttonStyle);

    this->illustrationbtn=new QPushButton("图鉴",this);
    this->illustrationbtn->setStyleSheet(buttonStyle);


    this->shopbtn=new QPushButton("商店",this);
    this->shopbtn->setStyleSheet(buttonStyle);


    this->quitbtn=new QPushButton("退出",this);
    this->quitbtn->setStyleSheet(buttonStyle);


    //创建垂直布局对象
    this->vboxlayout=new QVBoxLayout(this);
    this->vboxlayout->addWidget(label);
    this->vboxlayout->addWidget(startbtn);
    this->vboxlayout->addWidget(illustrationbtn);
    this->vboxlayout->addWidget(shopbtn);
    this->vboxlayout->addWidget(quitbtn);
    this->vboxlayout->setAlignment(Qt::AlignCenter);
    this->vboxlayout->setSpacing(30);









    //信号和槽关联
    this->connect(startbtn,SIGNAL(clicked()),this,SLOT(startbtnclick()));
    this->connect(quitbtn,SIGNAL(clicked()),this,SLOT(quitbtnclick()));
    this->connect(illustrationbtn,SIGNAL(clicked()),this,SLOT(illustrationbtnclick()));
    this->connect(shopbtn,SIGNAL(clicked()),this,SLOT(shopbtnclick()));

}

mainWidget::~mainWidget() {}

void mainWidget::startbtnclick(){

    this->hide();
    //游戏场景
    easyview = new  class EasyView(this);

    easyview->show();
}

void mainWidget::quitbtnclick()
{
    // 使用 QMessageBox::question 创建询问对话框
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,                                   // 父窗口
        tr("退出确认"),                         // 标题（支持国际化）
        tr("你是否确定要退出？"),               // 提示信息
        QMessageBox::Yes | QMessageBox::No,   // 按钮组合
        QMessageBox::No                       // 默认选中按钮,不填默认为Yes
        );

    // 处理用户选择
    if (reply == QMessageBox::Yes) {
        this->close();  // 允许关闭窗口
    }
}

void mainWidget::illustrationbtnclick()
{
    //图鉴
    illustration=new class illustration(this);
    illustration->show();
}
void mainWidget::shopbtnclick()
{
    //商店
    shop=new class shop(this);

    shop->show();
}
