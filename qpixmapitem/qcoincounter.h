#ifndef QCOINCOUNTER_H
#define QCOINCOUNTER_H
#include "qpixmapitem.h"
#include <QGraphicsTextItem>
#include <QFile>
#include <QDataStream>
class QCoinCounter:public QPixmapItem
{
public:
    QCoinCounter(QGraphicsItem* parent=nullptr);
    QCoinCounter(const QString & fileName,QGraphicsScene *scene);

    // 设置显示内容（例如 "100", "5X"）
    void setValue(const QString& value);
    // 数字增减接口
    bool add(int value);       // 捕获鱼时增加
    bool subtract(int value);  // 发射炮弹时减少

    //得到金币
    int getValue();

    // 数值边界检查
    bool canSubtract(int value) const;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
signals:
    void valueChanged(int newValue);  // 数值变化信号

private:
    const QString m_filePath = "userdata.gold.txt";
    int m_currentValue;        // 初始金币数（与图中UI风格匹配）
    void updateDisplay();             // 更新显示文本
    QString m_displayValue;          // 当前显示文本（如 "1000"）
    QPixmap m_charSheet;             // 原始字符图片（包含 0-9 和 X）
    QVector<QPixmap> m_charFrames;   // 切割后的字符帧（按顺序 0,1,2,...,9,X）

    // 根据图片调整以下参数
    int m_charWidth = 39;            // 单字符宽度（根据图片实际尺寸修改）
    int m_charHeight = 49;           // 单字符高度
    int m_totalChars = 10;           // 字符总数（0-9）

    int m_boxWidth = 20;      // 每个框的总宽度（包含边距）
    int m_boxHeight = 30;     // 每个框的总高度（包含边距）
    int m_horizontalSpacing = 3; // 框之间的水平间距
    QColor m_boxColor = QColor(0, 0, 0, 0); // 框颜色（金色半透明）

    bool loadFromFile();
    bool saveToFile();
};

#endif // QCOINCOUNTER_H
