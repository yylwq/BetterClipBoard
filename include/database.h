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
    void removeData(int id);
    void changeFavorite(const int &id, const bool &favo);

    QList<Data> getAllData();
    QList<Data> getRecentData(int limit);
    QList<Data> getFavoriteData(int limit);

    QList<Data> getAllDataByType(const DataType &type);
    int getCountByType(const DataType &type);
    Data getDataById(int id);

public slots:
    void qmlClickChangeFavorite(const int &id, const bool &favo, const QString& data_type);
    void qmlDeleteData(const int& id, const QString& data_type);

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

    void urlFavoriteChanged(const int& id, const bool &favo);
    void emailFavoriteChanged(const int& id, const bool &favo);
    void textFavoriteChanged(const int& id, const bool &favo);
    void magneticseedFavoriteChanged(const int& id, const bool &favo);
    void codeFavoriteChanged(const int& id, const bool &favo);
    void recentFavoriteChanged(const int& id, const bool &favo);
    void favoriteFavoriteChanged(const int& id, const bool &favo);

    void urlDeleteData(const int& id);
    void emailDeleteData(const int& id);
    void textDeleteData(const int& id);
    void magneticseedDeleteData(const int& id);
    void codeDeleteData(const int& id);
    void recentDeleteData(const int& id);
    void favoriteDeleteData(const int& id);

};
