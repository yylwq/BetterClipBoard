#include "../include/DataModel/favoritedatamodel.h"


FavoriteDataModel::FavoriteDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getFavoriteData(200);
    connect(database, &DataBase::insertedData, this, &FavoriteDataModel::updateDatas);
    connect(database, &DataBase::favoriteFavoriteChanged, this, &FavoriteDataModel::updateFavorite);
    connect(database, &DataBase::favoriteDeleteData, this, &FavoriteDataModel::deleteData);
}

void FavoriteDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    datas.push_front(data);
    endInsertRows();
}

void FavoriteDataModel::updateDatas(const Data &data)
{
    if (data.favorite == true)
        addData(data);
}

void FavoriteDataModel::updateFavorite(const int &id, const bool &favo)
{
    if (favo) {
        removeDataFromModel(id);
    } else {
        Data data = database->getDataById(id);
        if (data.id_ != -1)
            addData(data);
    }
}
