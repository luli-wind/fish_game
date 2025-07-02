#include "goldenshark_illustration.h"

goldenshark_illustration::goldenshark_illustration(QWidget *parent)
    : QWidget{parent}
{
    // 主布局：水平分栏（左图+右文）
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20); // 边距
    mainLayout->setSpacing(30); // 分栏间距

    // 左侧：图标与属性（垂直布局）
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setSpacing(15);

    // 鱼类图标（QPixmap 加载资源）
    QLabel *fishIcon = new QLabel;
    fishIcon->setPixmap(QPixmap(":/image/goldenshark1.png").scaled(200, 200, Qt::KeepAspectRatio));
    leftLayout->addWidget(fishIcon, 0, Qt::AlignCenter);

    // 属性数值（使用 QGridLayout 对齐标签和值）
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(10);

    QStringList labels = {"稀有度", "生命值", "价值:"};
    QStringList values = {"★★★★★", "10", "500金币"};

    for (int i = 0; i < labels.size(); ++i) {
        QLabel *label = new QLabel(labels[i]);
        QLabel *value = new QLabel(values[i]);
        label->setStyleSheet("background-color:#C0DEF5;color:#386487;font-size:25px; padding:3px;");
        value->setStyleSheet("background-color:#C0DEF5;color:#386487;font-size:20px;");
        gridLayout->addWidget(label, i, 0);
        gridLayout->addWidget(value, i, 1);
    }



    leftLayout->addLayout(gridLayout);
    mainLayout->addLayout(leftLayout);

    // 右侧：描述与交互（QTextBrowser 支持富文本）
    QTextBrowser *rightText = new QTextBrowser;
    rightText->setStyleSheet("background-color: #B0C4DE;");
    rightText->setOpenExternalLinks(false); // 禁用外部链接
    rightText->setFrameStyle(QFrame::NoFrame); // 无边框
    rightText->document()->setDocumentMargin(0); // 去除默认边距

    // 加载富文本内容（HTML + CSS）
    QString htmlContent = R"(
    <style>
        .title { color: #FF8C00; font-size: 24px; margin-bottom: 15px; }
        .subtitle { color: #000000; font-size: 16px; margin: 10px 0; }
        .highlight { color: #FAF9DE; font-weight: bold; }
        .box{background-color:#B0C4DE}
        p { color: #FFFFFF; font-size: 14px; line-height: 1.5; margin: 8px 0; }
    </style>
    <div class="box">
    <h1 class="title">​​​​​​​​黄金鲨鱼 GoldenShark​​​​​</h1>
    <span class="highlight" style="font-size:16px;">「深海中的黄金财宝」​​​</span>
    <p class="subtitle">📖 生态档案</p>
    <ul>
    <li><p><span class="highlight">​​鎏金之躯</span>​​：黄金布满全身，令人垂涎无法自拔。</p></li>
    <li><p><span class="highlight">​​财富共鸣</span>​​：这些黄金鲨鱼似乎见过one piece。</p></li>
    <li><p><span class="highlight">​​​​​​熔核之心​​</span>​​：黄金鲨鱼体内似乎有些了不得的东西。</p></li>
    </ul>

    <p class="subtitle">🎮 玩家提示</p>
    <p>🎣 ​​捕获技巧​​：孩子们，这是给你们的<span class="highlight">奖励​​</span>，一定要珍惜，错过了就不会再见了</p>
    </div>

)";
    rightText->setHtml(htmlContent);
    mainLayout->addWidget(rightText);
}
