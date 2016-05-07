#ifndef DBSETTINGDATA_H
#define DBSETTINGDATA_H

#include <QString>
#include "dbsettingerror.h"

struct DbSettingData
{
    QString databaseName;
    QString userName;
    QString password;
    QString hostName;
    DbSettingError error;
};

#endif // DBSETTINGDATA_H
