#include <QObject>

#include "const.h"
#include "data.h"

class DataBase
{
public:
    DataBase();

    void insertData(const Data &data);
    void removeDate(int id);
    QList<Data> getAllData();

private:
    QString database_path;
    QString database_name;
    QString table_name;

private:
    void initDatabase();
    void createTable();
};
