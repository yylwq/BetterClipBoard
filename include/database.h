#pragma once

#include <QObject>
#include <QSqlQuery>

#include "const.h"
#include "data.h"

class DataBase
{
public:
    DataBase();

    void insertData(const Data &data);
    void removeDate(int id);
    QList<Data> getAllData();
    QList<Data> getRecentData(int limit);

    // limit 返回的行数 offset 跳过的行数
    QList<Data> getDataByType(const DataType &type, int offset, int limit);
    int getCountByType(const DataType &type);

private:
    QString database_path;
    QString database_name;
    QString table_name;

private:
    void initDatabase();
    void createTable();

    static Data rowToData(const QSqlQuery &query);
};
