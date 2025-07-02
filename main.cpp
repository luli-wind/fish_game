#include "mainwidget.h"

#include <QApplication>
#include <QMetaType>
#include <QDataStream>


int main(int argc, char *argv[])
{
    // 注册流操作符（关键！）
    qRegisterMetaType<QList<int>>("QList<int>");
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    return a.exec();
}


// 实现序列化操作符
QDataStream& operator<<(QDataStream& out, const QList<int>& list) {
    out << static_cast<quint32>(list.size());
    for (int value : list) {
        out << value;
    }
    return out;
}

QDataStream& operator>>(QDataStream& in, QList<int>& list) {
    list.clear();
    quint32 size;
    in >> size;
    for (quint32 i = 0; i < size; ++i) {
        int value;
        in >> value;
        list.append(value);
    }
    return in;
}
