#include "../include/DataModel/favoritedatamodel.h"
#include <QDebug>

FavoriteDataModel::FavoriteDataModel(DataBase *database, QObject *parent,
                                     bool all, DataType t) :
    DataModel(database, parent),
    type(t),
    is_all(all)
{
    connect(database, &DataBase::insertedData, this, &FavoriteDataModel::updateDatas);
    connect(database, &DataBase::favoriteFavoriteChanged, this, &FavoriteDataModel::updateFavorite);
    connect(database, &DataBase::favoriteDeleteData, this, &FavoriteDataModel::deleteData);

    if (is_all) {
        datas = database->getFavoriteData(200);
    } else {
        datas = database->getFavoriteDataByType(type);
    }

    qDebug() << "[FavoriteDataModel] 初始加载:" << datas.size() << "条";
}

void FavoriteDataModel::addData(const Data &data)
{
    bool match = is_all || data.type_ == type;
    if (match) {
        beginInsertRows(QModelIndex(), 0, 0);
        datas.push_front(data);
        endInsertRows();
    }
}

void FavoriteDataModel::updateDatas(const Data &data)
{
    if (is_all || data.type_ == type)
    {
        if (data.favorite == true)
            addData(data);
    }
}

void FavoriteDataModel::updateFavorite(const int &id, const bool &favo, const DataType& data_type)
{  
    if (!is_all && type != data_type) {
        return;
    }

    if (favo) {
        removeDataFromModel(id);
    } else {
        Data data = database->getDataById(id);
        if (data.id_ != -1) {
            if (is_all || data.type_ == type)
                addData(data);
        }
    }
}
