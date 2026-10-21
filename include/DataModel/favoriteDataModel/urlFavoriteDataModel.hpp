#pragma once

#include <QAbstractListModel>

#include "../../data.h"
#include "../../const.h"
#include "../favoritedatamodel.h"

class UrlFavoriteDataModel : public FavoriteDataModel
{
    Q_OBJECT

public:
    explicit UrlFavoriteDataModel(DataBase *database, QObject *parent)
        : FavoriteDataModel(database, parent, false, DataType::Url)
    {}
};
