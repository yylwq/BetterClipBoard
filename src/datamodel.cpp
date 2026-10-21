#include "../include/DataModel/datamodel.h"

DataModel::DataModel(DataBase *database, QObject *parent)
    : QAbstractListModel(parent)
{
    this->database = database;
}



int DataModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : datas.size();
}



QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= datas.size())
        return {};

    const Data &data = datas[index.row()];

    switch (role)
    {
    case IdRole:        return data.id_;
    case TextRole:      return data.text_;
    case FavoriteRole:  return data.favorite;
    case TimestampRole: return data.timestamp_.toString(Qt::ISODate);
    case TypeRole:      return data.typeToString();
    case TagRole:       return data.tag_;
    }

    return QVariant();
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash.insert(IdRole, "id");
    hash.insert(TextRole, "text");
    hash.insert(FavoriteRole, "favorite");
    hash.insert(TimestampRole, "timestamp");
    hash.insert(TypeRole, "type");
    hash.insert(TagRole, "tag");

    return hash;
}


void DataModel::loadPage(const QString &type)
{
    beginResetModel();
    datas = database->getAllDataByType(stringToType(type));
    endResetModel();

    emit pageChanged();
}

void DataModel::loadRecentData(int limit)
{
    beginResetModel();
    datas = database->getRecentData(limit);
    endResetModel();

    emit pageChanged();
}

void DataModel::loadFavoriteData(int limit)
{
    beginResetModel();
    datas = database->getFavoriteData(limit);
    endResetModel();

    emit pageChanged();
}

void DataModel::updataFavoriteDataFromModel(const int &id, const bool &favo)
{
    for (int i = 0; i < datas.size(); ++i) {
        if (datas[i].id_ == id) {
            datas[i].favorite = (!favo);

            QModelIndex itemIndex = index(i, 0);
            emit dataChanged(itemIndex, itemIndex, {FavoriteRole});
            break;
        }
    }
}

void DataModel::removeDataFromModel(const int &id)
{
    for (int i = 0; i < datas.size(); ++i) {
        if (datas[i].id_ == id) {
            beginRemoveRows(QModelIndex(), i, i);
            datas.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}

void DataModel::updateFavorite(const int &id, const bool &favo, const DataType& data_type)
{
    updataFavoriteDataFromModel(id, favo);
}

void DataModel::deleteData(const int &id)
{
    removeDataFromModel(id);
}





