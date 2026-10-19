#include "../include/DataModel/favoritedatamodel.h"


FavoriteDataModel::FavoriteDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getFavoriteData(200);
    // connect(database, &DataBase::insertedData, this, &FavoriteDataModel::updateDatas);
}

void FavoriteDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    datas.push_front(data);
    endInsertRows();
}

void FavoriteDataModel::updateDatas(const Data &data)
{
    addData(data);
}
