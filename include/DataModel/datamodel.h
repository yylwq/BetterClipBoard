#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QList>

#include "../const.h"
#include "../data.h"
#include "../database.h"

class DataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles{
        IdRole = Qt::UserRole + 1,
        TextRole,
        FavoriteRole,
        TimestampRole,
        TypeRole,
        TagRole
    };

public:
    explicit DataModel(DataBase *database, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void loadPage(const QString &type);
    Q_INVOKABLE void loadRecentData(int limit = 200);
    Q_INVOKABLE void loadFavoriteData(int limit = 200);

    void updataFavoriteDataFromModel(const int& id, const bool &favo);
    void removeDataFromModel(const int &id);

public slots:
    virtual void updateDatas(const Data& data) = 0;
    virtual void updateFavorite(const int& id, const bool &favo);
    virtual void deleteData(const int& id);

protected:
    DataBase *database;
    QList<Data> datas;

signals:
    void pageChanged();
};

#endif // DATAMODEL_H
