#pragma once

#include <QAbstractListModel>

#include "datamodel.h"
#include "../const.h"
#include "../data.h"

// ALL favorite datas
class FavoriteDataModel : public DataModel
{
    Q_OBJECT

public:
    explicit FavoriteDataModel(DataBase *database, QObject *parent = nullptr,
                               bool all = true, DataType t = DataType::Text);

    void addData(const Data &data);

public slots:
    virtual void updateDatas(const Data& data) override;
    virtual void updateFavorite(const int& id, const bool &favo, const DataType& data_type) override;

protected:
    DataType type = DataType::Text;
    bool is_all = true;
};
