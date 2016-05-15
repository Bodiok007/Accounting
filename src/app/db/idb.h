#ifndef IDB_H
#define IDB_H

#include <QString>
#include <QtSql>
#include <QSharedPointer>
#include "dbsetting.h"

class IDb
{
public:
    /*bool query( QString &query,
                QStringList &arguments,
                QSqlQueryModel *model );*/

    virtual bool query( QString query,
                        QStringList &arguments ) = 0;
    /*virtual bool queryProcedure( QString &query,
                                 QStringList &arguments ) = 0;*/

    virtual bool query( QString query ) = 0;

    virtual QSqlError lastError() const = 0;
    virtual QVariant lastInsertId() const = 0;
    virtual QSharedPointer<QSqlQuery> getData() const = 0;

    virtual bool connectToDb( DbSettingData settingData ) = 0;
    virtual bool connectToDb() = 0;

    virtual QSharedPointer<DbSetting> getSetting() const = 0;
    virtual void setSetting( DbSettingData settingData ) = 0;
};

#endif // IDB_H
