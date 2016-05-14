#ifndef MYSQLDB_H
#define MYSQLDB_H

#include "idb.h"

class MySqlDb : public IDb
{
public:
    MySqlDb();

    bool connectToDb( DbSettingData settingData );
    bool connectToDb();

    QSharedPointer<DbSetting> getSetting() const;
    void setSetting( DbSettingData settingData );

    bool query( QString query,
                QStringList &arguments );
    /*bool queryProcedure( QString &query,
                         QStringList &arguments ) = 0;*/

    QSharedPointer<QSqlQuery> getData() const;
    QSqlError lastError() const;
    QVariant lastInsertId() const;

private:
    QSqlDatabase _db;
    QSharedPointer<DbSetting> _setting;
    QSharedPointer<QSqlQuery> _query;

private:
    void putSettingIntoDb();
    void logOpenDbError( QString fileName, int line );

    bool queryWithParameters( QString &query,
                              QStringList &arguments );
    /*bool queryProcedureWithParameters( QString &query,
                              QStringList &arguments );*/

    void closeConnectionIfDbOpen();

};

#endif // MYSQLDB_H
