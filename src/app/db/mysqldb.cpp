#include "mysqldb.h"


MySqlDb::MySqlDb()
{
    _db = QSqlDatabase::addDatabase( "QMYSQL" );
    _setting = QSharedPointer<DbSetting>( new DbSetting() );
    _query = QSharedPointer<QSqlQuery>( new QSqlQuery() );
    //connectToDb();
}


bool MySqlDb::connectToDb( DbSettingData settingData )
{
    closeConnectionIfDbOpen();

    setSetting( settingData );
    putSettingIntoDb();

    if ( !_db.open() ) {
        logOpenDbError( __FILE__, __LINE__ );
        return false;
    }

    return true;
}


bool MySqlDb::connectToDb()
{
    closeConnectionIfDbOpen();
    putSettingIntoDb();

    if ( !_db.open() ) {
        logOpenDbError( __FILE__, __LINE__ );
        return false;
    }

    return true;
}


void MySqlDb::closeConnectionIfDbOpen()
{
    if ( _db.isOpen() ) {
        _db.close();
    }
}


void MySqlDb::setSetting( DbSettingData settingData )
{
    _setting->saveSetting( settingData );
}


bool MySqlDb::query( QString &query, QStringList &arguments )
{
    bool statusOk = false;

    if ( arguments.size() > 0 ) {
        statusOk = queryWithParameters( query, arguments );
    }

    return statusOk;
}

QSharedPointer<QSqlQuery> MySqlDb::getData() const
{
    return _query;
}


bool MySqlDb::queryWithParameters( QString &query, QStringList &arguments )
{
    _query->prepare( query );
    foreach ( QString arg, arguments ) {
        _query->addBindValue( arg );
    }

    if ( !_query->exec() ) {
        return false;
    }

    return true;
}


QSqlError MySqlDb::lastError() const
{
    return _query->lastError();
}


QVariant MySqlDb::lastInsertId() const
{
   return _query->lastInsertId();
}


QSharedPointer<DbSetting> MySqlDb::getSetting() const
{
    return _setting;
}


void MySqlDb::putSettingIntoDb()
{
    auto setting = _setting->readSetting();

    _db.setDatabaseName( setting.databaseName );
    _db.setUserName( setting.userName );
    _db.setHostName( setting.hostName );
    _db.setPassword( setting.password );
}


void MySqlDb::logOpenDbError( QString fileName, int line )
{
    ErrorFileInfo errorInfo;
    errorInfo.setFileName( fileName );
    errorInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , QObject::tr( "Помилка при відкритті бази даних: " )
                                + _db.lastError().text() + QString("\n")
                                , errorInfo );
}




