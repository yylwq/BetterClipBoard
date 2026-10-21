#pragma once

#include <QAbstractListModel>

#include "../../data.h"
#include "../../const.h"
#include "../favoritedatamodel.h"

class MagneticSeedFavoriteDataModel : public FavoriteDataModel
{
    Q_OBJECT

public:
    explicit MagneticSeedFavoriteDataModel(DataBase *database, QObject *parent)
        : FavoriteDataModel(database, parent, false, DataType::MagneticSeed)
    {}
};
