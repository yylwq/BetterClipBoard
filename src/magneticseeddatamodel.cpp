#include "../include/DataModel/magneticseeddatamodel.h"

MagneticSeedDataModel::MagneticSeedDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getAllDataByType(DataType::MagneticSeed);
    connect(database, &DataBase::insertedData, this, &MagneticSeedDataModel::updateDatas);
}

void MagneticSeedDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), 0, 0);
    datas.push_front(data);
    endInsertRows();
}

void MagneticSeedDataModel::updateDatas(const Data &data)
{
    if (data.type_ == DataType::MagneticSeed)
        addData(data);
}
