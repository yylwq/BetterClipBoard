#pragma once

#include <QAbstractListModel>

#include "../../data.h"
#include "../../const.h"
#include "../favoritedatamodel.h"

class EmailFavoriteDataModel : public FavoriteDataModel
{
    Q_OBJECT

public:
    explicit EmailFavoriteDataModel(DataBase *database, QObject *parent)
        : FavoriteDataModel(database, parent, false, DataType::Email)
    {}
};
