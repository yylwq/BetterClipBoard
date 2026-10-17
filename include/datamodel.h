#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QList>

#include "const.h"
#include "data.h"
#include "database.h"

class DataModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString cur_type READ getCur_type WRITE setCur_type NOTIFY cur_typeChanged FINAL)
    Q_PROPERTY(int cur_page READ getCur_page WRITE setCur_page NOTIFY cur_pageChanged FINAL)
    Q_PROPERTY(int total_page READ getTotal_page WRITE setTotal_page NOTIFY total_pageChanged FINAL)

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

    int getCurPage() { return cur_page; }
    int totalPage() { return total_page; }
    QString currentType() const { return cur_type; }

    // 切换数据
    Q_INVOKABLE void loadPage(const QString &type, int page);
    Q_INVOKABLE void loadRecentData(int limit = 200);

    QString getCur_type() const;
    void setCur_type(const QString &newCur_type);

    int getCur_page() const;
    void setCur_page(int newCur_page);

    int getTotal_page() const;
    void setTotal_page(int newTotal_page);

private:
    DataBase *database;
    QList<Data> datas;
    QString cur_type;
    int cur_page = 1;
    int total_page = 1;

signals:
    void pageChanged();
    void cur_typeChanged();
    void cur_pageChanged();
    void total_pageChanged();
};

#endif // DATAMODEL_H
