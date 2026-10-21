#pragma once

#include <QAbstractListModel>

#include "../../data.h"
#include "../../const.h"
#include "../favoritedatamodel.h"

class TextFavoriteDataModel : public FavoriteDataModel
{
    Q_OBJECT

public:
    explicit TextFavoriteDataModel(DataBase *database, QObject *parent)
        : FavoriteDataModel(database, parent, false, DataType::Text)
    {}
};
