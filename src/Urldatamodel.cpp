#include "../include/DataModel/urlDataModel.h"


UrlDataModel::UrlDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getAllDataByType(DataType::Url);
    connect(database, &DataBase::insertedData, this, &UrlDataModel::updateDatas);
    connect(database, &DataBase::urlFavoriteChanged, this, &UrlDataModel::updateFavorite);
    connect(database, &DataBase::urlDeleteData, this, &UrlDataModel::deleteData);
}

void UrlDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    datas.push_front(data);
    endInsertRows();
}

void UrlDataModel::updateDatas(const Data &data)
{
    if (data.type_ == DataType::Url)
        addData(data);
}
