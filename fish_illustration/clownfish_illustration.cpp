#include "clownfish_illustration.h"

clownfish_illustration::clownfish_illustration(QWidget *parent)
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
    fishIcon->setPixmap(QPixmap(":/image/clownfish1.png").scaled(200, 200, Qt::KeepAspectRatio));
    leftLayout->addWidget(fishIcon, 0, Qt::AlignCenter);

    // 属性数值（使用 QGridLayout 对齐标签和值）
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setHorizontalSpacing(0);
    gridLayout->setVerticalSpacing(10);

    QStringList labels = {"稀有度", "生命值", "价值:"};
    QStringList values = {"★☆☆☆☆", "2", "30 金币"};

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
    <h1 class="title">小丑鱼 Clownfish</h1>
    <span class="highlight" style="font-size:16px;">「珊瑚礁中的共生舞者」​</span>
    <p class="subtitle">📖 生态档案</p>
    <ul>
    <li><p><span class="highlight">​​​​共生专家</span>​​：与海葵形成互利关系，体表黏液可免疫海葵毒素，并以海葵为巢穴躲避天敌。</p></li>
    <li><p><span class="highlight">性别转换</span>​​：族群由雌性首领统治，首领消失后，最强壮的雄鱼会变性继任，展现自然界的奇妙法则。</p></li>
    <li><p><span class="highlight">​​​​群体智慧​​</span>​​：常以家庭为单位群居，幼鱼体色较浅，随年龄增长呈现鲜明橙白条纹。</p></li>
    </ul>
    <p class="subtitle">🎮 玩家提示</p>
    <p>🎣 捕获技巧：优先攻击<span class="highlight">落单的小丑鱼</span>，小丑鱼易于捕获，很受各位玩家的青睐。
    </div>

)";
    rightText->setHtml(htmlContent);
    mainLayout->addWidget(rightText);
}
