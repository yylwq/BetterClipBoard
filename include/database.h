#pragma once

#include <QObject>
#include <QSqlQuery>

#include "const.h"
#include "data.h"

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);

    void insertData(const Data &data);
    void removeDate(int id);
    QList<Data> getAllData();
    QList<Data> getRecentData(int limit);
    QList<Data> getFavoriteData(int limit);

    QList<Data> getAllDataByType(const DataType &type);
    int getCountByType(const DataType &type);

private:
    QString database_path;
    QString database_name;
    QString table_name;

private:
    void initDatabase();
    void createTable();

    static Data rowToData(const QSqlQuery &query);

signals:
    void insertedData(const Data &data);
};
