#include "../include/DataModel/textDataModel.h"


TextDataModel::TextDataModel(DataBase *database, QObject *parent) : DataModel(database, parent)
{
    datas = database->getAllDataByType(DataType::Text);
    // connect(database, &DataBase::insertedData, this, &TextDataModel::updateDatas);
}

void TextDataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    datas.push_front(data);
    endInsertRows();
}

void TextDataModel::updateDatas(const Data &data)
{
    addData(data);
}
