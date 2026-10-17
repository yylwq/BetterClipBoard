#include "../include/database.h"

#include <QDir>
#include <QCoreApplication>

#include <QSqlDatabase>
#include <QList>
#include <QDateTime>

DataBase::DataBase()
{
    QString effectivePath;

    QDir appDir(QCoreApplication::applicationDirPath());
    appDir.cdUp();
    appDir.cdUp();

    effectivePath = appDir.absoluteFilePath("data");

    QDir dataDir(effectivePath);
    if (!dataDir.exists()) {
        if (!dataDir.mkpath(".")) {
            qWarning() << "创建 data 目录失败:" << effectivePath;
        }
        qDebug() << "已创建 data 目录:" << effectivePath;
    } else {
        qDebug() << "data 目录已存在:" << effectivePath;
    }

    database_name = "BetterCB_data.db";

    database_path = dataDir.absoluteFilePath(database_name);

    qDebug() << "database_path: " << database_path;

    qDebug() << "正在初始化数据库!";
    initDatabase();
}



void DataBase::insertData(const Data &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO datas (content, timestamp, type, tag) VALUES (?, ?, ?, ?);");
    query.addBindValue(data.text_);
    query.addBindValue(data.timestamp_.toString(Qt::ISODate));
    query.addBindValue(data.typeToString());
    query.addBindValue(data.tag_);
    if (!query.exec())
    {
        qDebug() << "数据插入失败!";
        qDebug() << "SQL:" << query.lastQuery();
        return;
    }
    qDebug() << "[SQL] 插入一条数据：" << data.timestamp_.toString(Qt::ISODate) << " " <<data.text_ << " " << data.typeToString();
}

void DataBase::removeDate(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM datas WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "删除失败！";
        qDebug() << "SQL: " << query.lastQuery();
    }
}

QList<Data> DataBase::getAllData()
{
    QList<Data> datas;

    QSqlQuery query;
    QString sql = "SELECT id, content, favorite, timestamp, type, tag FROM ";
    sql += table_name;

    if (!query.exec(sql))
    {
        qDebug() << "数据读取失败!";
        qDebug() << "SQL:" << query.lastQuery();
        return datas;
    }

    while (query.next())
    {
        Data data = rowToData(query);
        datas.push_back(data);
    }
    return datas;
}

QList<Data> DataBase::getRecentData(int limit)
{
    QList<Data> datas;

    QSqlQuery query;
    const QString sql =
        "SELECT id, content, favorite, timestamp, type, tag FROM " + table_name +
        "ORDER BY timestamp DESC LIMIT ?";
    query.prepare(sql);
    query.addBindValue(limit);

    if (!query.exec())
    {
        qDebug() << "查询失败";
        qDebug() << "sql:" << query.lastQuery();
        return datas;
    }

    while (query.next())
    {
        Data data = rowToData(query);
        datas.push_back(data);
    }
    return datas;
}

QList<Data> DataBase::getDataByType(const DataType &type, int offset, int limit)
{
    QList<Data> datas;

    QSqlQuery query;
    const QString sql =
        "SELECT id, content, favorite, timestamp, type, tag FROM " + table_name +
        " WHERE type = ? ORDER BY timestamp DESC LIMIT ? OFFSET ?";
    query.prepare(sql);
    query.addBindValue(typeToString(type));
    query.addBindValue(limit);
    query.addBindValue(offset);

    if (!query.exec())
    {
        qDebug() << "查询失败";
        qDebug() << "sql:" << query.lastQuery();
        return datas;
    }

    while (query.next())
    {
        Data data = rowToData(query);
        datas.push_back(data);
    }
    return datas;
}

int DataBase::getCountByType(const DataType &type)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM" + table_name + "WHERE type = ?");
    query.addBindValue(typeToString(type));

    if (!query.exec() || !query.next())
    {
        qDebug() << "查询失败";
        qDebug() << "sql:" << query.lastQuery();
        return -1;
    }

    return query.value(0).toInt();
}

void DataBase::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(database_path);

    if (!db.open())
    {
        qDebug() << "数据库开启失败!";
        return;
    }

    qDebug() << "数据库正在建表!";
    createTable();
}

void DataBase::createTable()
{
    QSqlQuery query;
    QString createTableSql = "CREATE TABLE IF NOT EXISTS datas(id INTEGER PRIMARY KEY AUTOINCREMENT, content TEXT, favorite INTEGER DEFAULT 0, timestamp TEXT, type TEXT NOT NULL, tag TEXT);";

    if (!query.exec(createTableSql))
    {
        qDebug() << "无法建表!";
        return;
    }

    table_name = "datas";
    qDebug() << "建表成功!";
}

Data DataBase::rowToData(const QSqlQuery &query)
{
    Data data;
    data.id_ = query.value("id").toInt();
    data.text_ = query.value("content").toString();
    data.favorite = query.value("favorite").toBool();
    data.timestamp_ = query.value("timestamp").toDateTime();
    data.type_ = stringToType(query.value("type").toString());
    data.tag_ = query.value("timestamp").toString();

    return data;
}
