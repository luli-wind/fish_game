#include "shop.h"
#include "cannonmanager.h"
#include <QMessageBox>
shop::shop(QWidget *parent): QWidget{parent}
{
    this->parent=parent;
    this->setFixedSize(1024, 768);  // 同时设置最小和最大尺寸
    this->setWindowTitle("捕鱼达人");//设置窗口标题
    this->setWindowIcon(QIcon(":/image/icon.png"));//设置窗口图标
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(235,245,255));  // 浅蓝色
    this->setAutoFillBackground(true);  // 必须启用自动填充
    this->setPalette(pal);
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
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    // 上半部分：商品滚动区域（占70%高度）
    productArea = new QScrollArea;
    productArea->setWidgetResizable(true);
    QWidget* productContainer = new QWidget;
    productLayout = new QVBoxLayout(productContainer);
    productArea->setWidget(productContainer);  // 关键：设置滚动区域内容
    initProducts();
    // 下半部分：底部面板（金币显示 + 返回按钮）
    QWidget* bottomPanel = new QWidget;
    bottomLayout = new QHBoxLayout(bottomPanel);
    bottomLayout->addStretch(1);  // 添加弹性空间
    coinCounter = new QCoinCounter();

    coinLabel = new QLabel();
    setCoinValue(coinCounter->getValue());
    coinLabel->setFixedSize(130,40);
    coinLabel->setStyleSheet("color: black; font-size: 16px;font-weight:bold; border: 3px solid #87CEFA;border-radius: 4px;padding:5px");
    bottomLayout->addWidget(coinLabel, 0, Qt::AlignLeft);
    bottomLayout->addStretch(80);
    bottomLayout->addWidget(returnbtn, 0, Qt::AlignRight);  // 按钮右对齐

    // 将上下部分加入主布局
    mainLayout->addWidget(productArea, 8);
    mainLayout->addWidget(bottomPanel, 2);

    this->setLayout(mainLayout);  // 应用布局到窗口[1,6](@ref)


    this->connect(returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnclick()));
}

void shop::returnbtnclick()
{
    this->close();

}

void shop::initProducts() {

    QString buttonStyle =
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #87CEEB, stop:1 #4682B4);" // 渐变色
        "    border: 1px solid #1E90FF;"       // 边框颜色
        "    border-radius: 4px;"              // 圆角半径
        "    color: white;"                    // 文字颜色
        "    padding: 5px 10px;"               // 内边距
        "    font-size: 18px;"                 // 字体大小
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                stop:0 #6495ED, stop:1 #4169E1);" // 悬停渐变
        "}"
        "QPushButton:pressed {"
        "    background: #4169E1;"             // 按下颜色
        "}"
        "QPushButton:disabled {"                // 禁用状态
        "    background: #D3D3D3;"             // 灰色背景
        "    border-color: #A9A9A9;"           // 深灰边框
        "    color: #696969;"                   // 深灰文字
        "}";

    QList<QStringList> products = {
        {"二级大炮", "100", ":/image/gun2.png","2"},
        {"三级大炮", "200", ":/image/gun3.png","3"},
        {"四级大炮", "300", ":/image/gun4.png","4"},
        {"五级大炮", "400", ":/image/gun5.png","5"},
        {"六级大炮", "500", ":/image/gun6.png","6"},
        {"七级大炮", "600", ":/image/gun7.png","7"}
    };
     auto* manager = CannonManager::instance();

    for (const auto& product : products) {
        QWidget* itemWidget = new QWidget;
        QHBoxLayout* itemLayout = new QHBoxLayout(itemWidget);

        // 商品图片
        QLabel* imgLabel = new QLabel;
        imgLabel->setPixmap(QPixmap(product[2]).scaled(100, 100));
        imgLabel->setStyleSheet("QLabel { border: 2px solid #1E90FF; border-radius:5px; padding:2px; }"); // [7,8](@ref)
        itemLayout->addWidget(imgLabel);
        itemLayout->addStretch(20);
        // 商品信息（名称+价格）
        QVBoxLayout* infoLayout = new QVBoxLayout;
        QLabel* nameLabel = new QLabel(product[0]);
         nameLabel->setStyleSheet("font-size:22px; font-weight:bold; color:#2F4F4F;"); // [1](@ref)
        QLabel* priceLabel = new QLabel(QString("价格: %1金币").arg(product[1]));
         priceLabel->setStyleSheet("font-size:18px; color:#556B2F; font-style:italic;"); // [3](@ref)
        infoLayout->addWidget(nameLabel);

        infoLayout->addWidget(priceLabel);
        itemLayout->addLayout(infoLayout);
        itemLayout->addStretch(20);
        // 购买按钮
        QPushButton* buyBtn = new QPushButton("购买");
        buyBtn->setStyleSheet(buttonStyle);
        if(manager->hasLevel(product[3].toInt()))
        {
            buyBtn->setEnabled(false);
            buyBtn->setText("已购买");
        }


         buyBtn->setCursor(Qt::PointingHandCursor);
        itemLayout->addWidget(buyBtn);

         connect(buyBtn, &QPushButton::clicked, [=](){
            int value =product[1].toInt();

            if (coinCounter->subtract(value)) {

                QMessageBox::StandardButton reply = QMessageBox::question(
                    this,                                   // 父窗口
                    tr("购买确认"),                         // 标题（支持国际化）
                    tr("你是否确定要购买？强烈推荐按顺序购买哦！"),               // 提示信息
                    QMessageBox::Yes | QMessageBox::No,   // 按钮组合
                    QMessageBox::No                       // 默认选中按钮,不填默认为Yes
                    );

                // 处理用户选择
                if (reply == QMessageBox::Yes) {
                    int level = product[3].toInt();
                    manager->purchaseLevel(level);
                    buyBtn->setEnabled(false);
                    buyBtn->setText("已购买");

                    setCoinValue(value);
                }


             } else {
                QMessageBox::warning(this, "金币不足", "赶紧捕鱼去获得更多的金币吧！");
             }
         });

        productLayout->addWidget(itemWidget);  // 加入商品列表布局[6,7](@ref)
    }
}

void shop::setCoinValue(int value)
{
    coins = coinCounter->getValue();
    QString coin =  QString("金币:%1").arg(coins);
    coinLabel->setText(coin);
}
