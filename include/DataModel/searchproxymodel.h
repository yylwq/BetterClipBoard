#pragma once

#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QDate>

#include "../const.h"
#include "datamodel.h"

class SearchProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString keyword READ getKeyword WRITE setKeyword NOTIFY keywordChanged FINAL)
    Q_PROPERTY(QString timeRange READ getTimeRange WRITE setTimeRange NOTIFY timeRangeChanged FINAL)
    Q_PROPERTY(QString sortOrder READ getSortOrder WRITE setSortOrder NOTIFY sortOrderChanged FINAL)

public:
    explicit SearchProxyModel(QObject *parent = nullptr);

    void setSourceModel(QAbstractItemModel *sourceModel) override;

    QString getKeyword() const;
    void setKeyword(const QString &newKeyword);

    QString getTimeRange() const;
    void setTimeRange(const QString &newTimeRange);

    QString getSortOrder() const;
    void setSortOrder(const QString &newSortOrder);

protected:
    // 筛选策略 返回true即保留
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    // 比较策略 返回true则 left > right
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QString keyword;
    QString timeRange;
    QString sortOrder;

signals:
    void keywordChanged();
    void timeRangeChanged();
    void sortOrderChanged();
};
