#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <QDateTime>
#include <QList>

#include "const.h"

enum DataType
{
    Text,
    Code,
    Email
};

struct Data
{
    int id_ = -1;
    QString text_;
    QImage image_;
    bool favorite;
    QDateTime timestamp_;
    DataType type_;
    QString tag_;

    QString typeToString() const
    {
        if (type_ == Text) return "文本";
        if (type_ == Code) return "代码";
        if (type_ == Email) return "邮箱";
        return "";
    }
};

static QString getTag(DataType date_type)
{
    switch (date_type)
    {
    case Text: return "文本";
    case Code: return "代码";
    case Email: return "邮箱";
    }
    return "";
}

static QString typeToString(const DataType &type)
{
    if (type == Text) return "文本";
    if (type == Code) return "代码";
    if (type == Email) return "邮箱";
    return "";
}

static DataType stringToType(const QString &type)
{
    if (type == "文本") return Text;
    if (type == "代码") return Code;
    if (type == "邮箱") return Email;
    return Text;
}

static void printData(QList<Data> datas)
{
    qDebug() << "开始打印数据!";
    qDebug() << "数据总量: " << datas.size();
    for (auto &data : datas)
    {
        qDebug() << "[" << data.timestamp_.toString(Qt::ISODate) << "] " << data.text_;
    }
    qDebug() << "数据打印结束!";
}

#endif // DATA_H
