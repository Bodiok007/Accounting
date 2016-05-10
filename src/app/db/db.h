#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSharedPointer>
#include "mysqldb.h"

class Db : public QObject
{
    Q_OBJECT

public:
    static QSharedPointer<Db> getInstance();

    bool connectToDb();
    bool connectToDb( DbSettingData settingData );

    QSharedPointer<DbSetting> getSetting() const;
    void setSetting( DbSettingData settingData );

    bool query( QString &query,
                QStringList &arguments );

    QSharedPointer<QSqlQuery> getData() const;
    QSqlError lastError() const;
    QVariant lastInsertId() const;

signals:

public slots:

private:
    Db( IDb *dbRepository , QObject *parent = 0 );
    static QSharedPointer<Db> _instance;

    QSharedPointer<IDb>_db;

private:
    void logError(QString fileName, int line );
};

#endif // DB_H
