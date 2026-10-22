#include "../include/DataModel/searchproxymodel.h"
#include "../include/DataModel/datamodel.h"

SearchProxyModel::SearchProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent),
      timeRange("all"),
      sortOrder("newest")
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void SearchProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);
    if (sourceModel) {
        setSortRole(DataModel::TimestampRole);
        sort(0, sortOrder == "newest" ? Qt::DescendingOrder : Qt::AscendingOrder);
    }
}

bool SearchProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent))
        return false;

    if (timeRange == "all" || timeRange.isEmpty())
        return true;

    QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
    QString ts = sourceModel()->data(idx, DataModel::TimestampRole).toString();

    QDateTime t = QDateTime::fromString(ts, Qt::ISODate);
    if (!t.isValid()) return true;
    t = t.toLocalTime();

    const QDate today = QDate::currentDate();
    const QDateTime todayStart = today.startOfDay();

    if (timeRange == "today")
        return t >= todayStart;

    if (timeRange == "week")
        return t >= today.addDays(-6).startOfDay();

    if (timeRange == "14days")
        return t >= today.addDays(-13).startOfDay();

    return true;
}

bool SearchProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant lv = sourceModel()->data(left, DataModel::TimestampRole);
    QVariant rv = sourceModel()->data(right, DataModel::TimestampRole);

    QDateTime lt = QDateTime::fromString(lv.toString(), Qt::ISODate);
    QDateTime rt = QDateTime::fromString(rv.toString(), Qt::ISODate);

    if (lt.isValid() && rt.isValid())
        return lt < rt;

    return sourceModel()->data(left, DataModel::IdRole).toInt() <
           sourceModel()->data(right, DataModel::IdRole).toInt();
}

QString SearchProxyModel::getKeyword() const   { return keyword; }
QString SearchProxyModel::getTimeRange() const { return timeRange; }
QString SearchProxyModel::getSortOrder() const { return sortOrder; }

void SearchProxyModel::setKeyword(const QString &newKeyword)
{
    if (keyword == newKeyword) return;
    keyword = newKeyword;
    setFilterFixedString(keyword);
    setFilterRole(DataModel::TextRole);
    invalidateFilter();
    emit keywordChanged();
}

void SearchProxyModel::setTimeRange(const QString &newRange)
{
    if (timeRange == newRange) return;
    timeRange = newRange;
    invalidateFilter();
    emit timeRangeChanged();
}

void SearchProxyModel::setSortOrder(const QString &newOrder)
{
    if (sortOrder == newOrder) return;
    sortOrder = newOrder;
    sort(0, newOrder == "newest" ? Qt::DescendingOrder : Qt::AscendingOrder);
    emit sortOrderChanged();
}
