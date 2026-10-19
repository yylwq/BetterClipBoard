#include "../include/DataModel/urlDataModel.h"


UrlDataModel::UrlDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getAllDataByType(DataType::Url);
    // connect(database, &DataBase::insertedData, this, &UrlDataModel::updateDatas);
}

void UrlDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    datas.push_front(data);
    endInsertRows();
}

void UrlDataModel::updateDatas(const Data &data)
{
    addData(data);
}
