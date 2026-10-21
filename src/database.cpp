#include "../include/database.h"

#include <QDir>
#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlError>
#include <QList>
#include <QDateTime>

DataBase::DataBase(QObject *parent) : QObject(parent)
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
    query.prepare("INSERT INTO datas (content, favorite, timestamp, type, tag) VALUES (?, ?, ?, ?, ?);");
    query.addBindValue(data.text_);
    query.addBindValue(data.favorite ? 1 : 0);
    query.addBindValue(data.timestamp_.toString(Qt::ISODate));
    query.addBindValue(data.typeToString());
    query.addBindValue(data.tag_);
    if (!query.exec())
    {
        qDebug() << "数据插入失败!";
        qDebug() << "SQL:" << query.lastQuery();
        return;
    }

    Data emitted = data;
    emitted.id_ = query.lastInsertId().toInt();
    qDebug() << "[SQL] 插入成功 id=" << emitted.id_
             << emitted.timestamp_.toString(Qt::ISODate)
             << emitted.text_ << typeToString(emitted.type_);

    emit insertedData(emitted);
}

void DataBase::removeData(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM datas WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "[removeDate(int id)] 删除失败！";
        qDebug() << "SQL: " << query.lastQuery();
    }
}

void DataBase::changeFavorite(const int& id, const bool &favo)
{
    QSqlQuery query;
    query.prepare("UPDATE " + table_name +" SET favorite = ? WHERE id = ?");
    if (favo)
    {
        query.addBindValue(false);
    }else{
        query.addBindValue(true);
    }

    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "[changeFavorite(const int& id, const bool &favo)] 更新star失败！";
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
        qDebug() << "[getAllData()] 数据读取失败!";
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
        " ORDER BY timestamp DESC LIMIT ?";
    query.prepare(sql);
    query.addBindValue(limit);

    if (!query.exec())
    {
        qDebug() << "[getRecentData(int limit)] 查询失败";
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

QList<Data> DataBase::getFavoriteData(int limit)
{
    QList<Data> datas;

    QSqlQuery query;
    const QString sql =
        "SELECT id, content, favorite, timestamp, type, tag FROM " + table_name +
        " WHERE favorite = 1 ORDER BY timestamp DESC LIMIT ?";
    query.prepare(sql);
    query.addBindValue(limit);

    if (!query.exec())
    {
        qDebug() << "[getFavoriteData(int limit)] 查询失败";
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

QList<Data> DataBase::getFavoriteDataByType(DataType type)
{
    QList<Data> datas;

    QSqlQuery query;
    const QString sql =
        "SELECT id, content, favorite, timestamp, type, tag FROM " + table_name +
        " WHERE type = ? AND favorite = 1 ORDER BY timestamp DESC";

    query.prepare(sql);
    query.addBindValue(typeToString(type));

    if (!query.exec())
    {
        qDebug() << "[getFavoriteDataByType(DataType type)] 查询失败";
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


QList<Data> DataBase::getAllDataByType(const DataType &type)
{
    QList<Data> datas;

    QSqlQuery query;
    const QString sql =
        "SELECT id, content, favorite, timestamp, type, tag FROM " + table_name +
        " WHERE type = ? ORDER BY timestamp DESC";
    query.prepare(sql);
    query.addBindValue(typeToString(type));

    if (!query.exec())
    {
        qDebug() << "[getAllDataByType(const DataType &type)] 查询失败";
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
    query.prepare("SELECT COUNT(*) FROM " + table_name + " WHERE type = ?");
    query.addBindValue(typeToString(type));

    if (!query.exec() || !query.next())
    {
        qDebug() << "[getCountByType(const DataType &type)] 查询失败";
        qDebug() << "sql:" << query.lastQuery();
        return -1;
    }

    return query.value(0).toInt();
}

Data DataBase::getDataById(int id)
{
    Data data;
    QSqlQuery query;
    query.prepare("SELECT id, content, favorite, timestamp, type, tag FROM " + table_name + " WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec())
    {
        qDebug() << "[getDataById] SQL 执行失败 id=" << id;
        qDebug() << "  error:" << query.lastError().text();
        qDebug() << "  sql:" << query.lastQuery();
        return data;
    }
    if (!query.next())
    {
        qDebug() << "[getDataById] 未找到 id=" << id;
        qDebug() << "  表中总行数:";
        QSqlQuery cq;
        cq.exec("SELECT COUNT(*) FROM " + table_name);
        if (cq.next()) qDebug() << "    count =" << cq.value(0).toInt();
        return data;
    }

    return rowToData(query);
}

void DataBase::qmlClickChangeFavorite(const int &id, const bool &favo, const QString& data_type)
{
    changeFavorite(id, favo);

    DataType dt = stringToType(data_type);

    switch (dt)
    {
    case DataType::Code:
        emit codeFavoriteChanged(id, favo, dt);
        break;
    case DataType::Email:
        emit emailFavoriteChanged(id, favo, dt);
        break;
    case DataType::MagneticSeed:
        emit magneticseedFavoriteChanged(id, favo, dt);
        break;
    case DataType::Url:
        emit urlFavoriteChanged(id, favo, dt);
        break;
    default:
        emit textFavoriteChanged(id, favo, dt);
    }

    emit favoriteFavoriteChanged(id, favo, dt);
    emit recentFavoriteChanged(id, favo, dt);
}

void DataBase::qmlDeleteData(const int &id, const QString &data_type)
{
    removeData(id);

    DataType dt = stringToType(data_type);

    switch (dt)
    {
    case DataType::Code:
        emit codeDeleteData(id);
        break;
    case DataType::Email:
        emit emailDeleteData(id);
        break;
    case DataType::MagneticSeed:
        emit magneticseedDeleteData(id);
        break;
    case DataType::Url:
        emit urlDeleteData(id);
        break;
    default:
        emit textDeleteData(id);
    }

    emit favoriteDeleteData(id);
    emit recentDeleteData(id);
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
    data.tag_ = query.value("tag").toString();

    return data;
}
