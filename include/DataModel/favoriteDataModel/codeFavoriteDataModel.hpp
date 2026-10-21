#pragma once

#include <QAbstractListModel>

#include "../../data.h"
#include "../../const.h"
#include "../favoritedatamodel.h"

class CodeFavoriteDataModel : public FavoriteDataModel
{
    Q_OBJECT

public:
    explicit CodeFavoriteDataModel(DataBase *database, QObject *parent)
        : FavoriteDataModel(database, parent, false, DataType::Code)
    {}
};
