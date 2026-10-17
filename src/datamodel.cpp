#include "../include/datamodel.h"

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

void DataModel::loadPage(const QString &type, int page)
{
    cur_type = type;
    cur_page = page;

    const int page_size = 20;
    const int total_count = database->getCountByType(stringToType(type));

    total_page = qMax(1, (total_count + page_size - 1) / page_size);

    if (cur_page > total_page)
    {
        cur_page = total_page;
    }

    int offset = (cur_page - 1) * page_size;

    beginResetModel();
    datas = database->getDataByType(stringToType(type), offset, page_size);
    endResetModel();

    emit pageChanged();
}

void DataModel::loadRecentData(int limit)
{
    cur_page = 1;
    total_page = 1;

    cur_type = "__recent__";
    beginResetModel();
    datas = database->getRecentData(limit);
    endResetModel();

    emit pageChanged();
}

QString DataModel::getCur_type() const
{
    return cur_type;
}

void DataModel::setCur_type(const QString &newCur_type)
{
    if (cur_type == newCur_type)
        return;
    cur_type = newCur_type;
    emit cur_typeChanged();
}

int DataModel::getCur_page() const
{
    return cur_page;
}

void DataModel::setCur_page(int newCur_page)
{
    if (cur_page == newCur_page)
        return;
    cur_page = newCur_page;
    emit cur_pageChanged();
}

int DataModel::getTotal_page() const
{
    return total_page;
}

void DataModel::setTotal_page(int newTotal_page)
{
    if (total_page == newTotal_page)
        return;
    total_page = newTotal_page;
    emit total_pageChanged();
}
