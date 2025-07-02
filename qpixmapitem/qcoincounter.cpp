#include "qcoincounter.h"

QCoinCounter::QCoinCounter(const QString & fileName,QGraphicsScene *scene):QPixmapItem(fileName,scene)
{


}

QCoinCounter::QCoinCounter(QGraphicsItem* parent):QPixmapItem("",nullptr)
{
    m_charSheet = QPixmap(":/image/coinText.png"); // 替换为你的图片路径
    QVector<QPair<int, int>> charLayout = {
        {0, 39},   // 0
        {39, 34},  // 1
        {73, 37},  // 2
        {110, 36},  // 3
        {146, 36}, // 4
        {182, 35}, // 5
        {217, 37}, // 6
        {254, 36}, // 7
        {290, 37}, // 8
        {327, 36}, // 9


    };

    // 目标缩小参数（保持原宽高比 3:4）
    int targetWidth = 15;
    int targetHeight = 24;

    // 切割字符帧（0-9）
    for (const auto& [x, w] : charLayout) {
        QPixmap originalFrame = m_charSheet.copy(x, 0, w, m_charHeight);
        QPixmap scaledFrame = originalFrame.scaled(
            targetWidth,
            targetHeight,
            Qt::KeepAspectRatio,          // 保持宽高比
            Qt::SmoothTransformation      // 平滑缩放（避免锯齿）
            );
        m_charFrames.append(scaledFrame);
    }
    // 更新字符尺寸参数（必须！）
    m_charWidth = targetWidth;
    m_charHeight = targetHeight;

    loadFromFile();
    setValue(QString("%1").arg(m_currentValue, 6, 10, QLatin1Char('0')));

    //setValue("001000"); // 初始值
    //m_currentValue=1000;
    saveToFile();
}

void QCoinCounter::setValue(const QString& value) {
    m_displayValue = value;
    update(); // 触发重绘
}

bool QCoinCounter::add(int value) {
    bool ok;
    int num = m_displayValue.toInt(&ok);
    if (!ok) {
        setValue("XXXXXX"); // 无效数值时显示错误
        return false;
    }

    num += value;
    // 处理溢出（假设最大值为999999）
    if (num > 999999) {
        setValue("XXXXXX");
        return false;
    }
    // 格式化为6位数字，补足前导零
    m_currentValue=num;
    saveToFile();
    setValue(QString("%1").arg(num, 6, 10, QLatin1Char('0')));
    return true;
}

bool QCoinCounter::subtract(int value) {
    bool ok;
    int num = m_displayValue.toInt(&ok);
    if (!ok || num < value) {
        setValue("XXXXXX"); // 数值不足或无效时显示错误
        return false;
    }

    num -= value;
    m_currentValue=num;
    saveToFile();
    setValue(QString("%1").arg(num, 6, 10, QLatin1Char('0')));
    return true;
}

QRectF QCoinCounter::boundingRect() const {
    int totalWidth = m_displayValue.length() * (m_boxWidth + m_horizontalSpacing) - m_horizontalSpacing;
    return QRectF(0, 0, totalWidth, m_boxHeight);
}

void QCoinCounter::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(m_boxColor)); // 设置框填充色
    painter->setPen(Qt::NoPen);            // 取消边框线

    int xPos = 0;
    for (const QChar& c : m_displayValue) {
        int index = -1;
        if (c >= '0' && c <= '9') {
            index = c.unicode() - '0';
        }

        if (index >= 0 && index < m_charFrames.size()) {
            // 绘制背景框
            painter->drawRoundedRect(xPos, 0, m_boxWidth, m_boxHeight, 0, 0);

            // 在框内居中绘制字符
            int charX = xPos + (m_boxWidth - 15) / 2;  // 水平居中
            int charY = (m_boxHeight - 24) / 2;        // 垂直居中
            painter->drawPixmap(charX, charY, m_charFrames[index]);

            xPos += m_boxWidth + m_horizontalSpacing;  // 累加位置
        }
    }
}

bool QCoinCounter::loadFromFile() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QTextStream  in(&file);
    //in.setVersion(QDataStream::Qt_5_15); // 设置流版本[6](@ref)
    in.setEncoding(QStringConverter::Utf8);
    in >> m_currentValue;
    file.close();
    return in.status() == QTextStream::Ok;
}

bool QCoinCounter::saveToFile() {
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;

    QTextStream out(&file);
    //out.setVersion(QDataStream::Qt_5_15); // 保持版本一致[6](@ref)
    out.setEncoding(QStringConverter::Utf8); // 显式设置编码
    out << m_currentValue;
    file.close();
    return out.status() == QTextStream::Ok;
}

int QCoinCounter::getValue()
{
    return m_currentValue;
}
