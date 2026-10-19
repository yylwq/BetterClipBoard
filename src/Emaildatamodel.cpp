#include "../include/DataModel/emaildatamodel.h"


EmailDataModel::EmailDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getAllDataByType(DataType::Email);
    connect(this->database, &DataBase::insertedData, this, &EmailDataModel::updateDatas);
}

void EmailDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    datas.push_front(data);
    endInsertRows();
}

void EmailDataModel::updateDatas(const Data &data)
{
    if (data.type_ == DataType::Email)
        addData(data);
}
