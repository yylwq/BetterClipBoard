#pragma once

#include <QAbstractListModel>

#include "datamodel.h"
#include "../const.h"
#include "../data.h"

class RecentDataModel : public DataModel
{
    Q_OBJECT

public:
    explicit RecentDataModel(DataBase *database, QObject *parent = nullptr);

    void addData(const Data &data);

public slots:
    virtual void updateDatas(const Data& data) override;

private:
};

