#include "../include/DataModel/recentdatamodel.h"


RecentDataModel::RecentDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getRecentData(200);
    connect(database, &DataBase::insertedData, this, &RecentDataModel::updateDatas);
}

void RecentDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    datas.push_front(data);
    endInsertRows();
}

void RecentDataModel::updateDatas(const Data &data)
{
    addData(data);
}
