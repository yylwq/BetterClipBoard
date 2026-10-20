#pragma once

#include <QAbstractListModel>

#include "datamodel.h"
#include "../const.h"
#include "../data.h"

class FavoriteDataModel : public DataModel
{
    Q_OBJECT

public:
    explicit FavoriteDataModel(DataBase *database, QObject *parent = nullptr);

    void addData(const Data &data);

public slots:
    virtual void updateDatas(const Data& data) override;

    virtual void updateFavorite(const int& id, const bool &favo) override;

private:
};


