#include "../include/DataModel/codedatamodel.h"

CodeDataModel::CodeDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getAllDataByType(DataType::Code);
    connect(database, &DataBase::insertedData, this, &CodeDataModel::updateDatas);
    connect(database, &DataBase::codeFavoriteChanged, this, &CodeDataModel::updateFavorite);
    connect(database, &DataBase::codeDeleteData, this, &CodeDataModel::deleteData);
}

void CodeDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    datas.push_front(data);
    endInsertRows();
}

void CodeDataModel::updateDatas(const Data &data)
{
    if (data.type_ == DataType::Code)
        addData(data);
}
