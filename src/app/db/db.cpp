#include "db.h"


Db::Db( IDb *dbRepository, QObject *parent ) : QObject( parent )
{
    _db = QSharedPointer<IDb>( dbRepository );
    _db->connectToDb();
}


QSharedPointer<Db> Db::getInstance()
{
    if ( _instance.isNull() ) {
        _instance = QSharedPointer<Db>(
                    new Db( new MySqlDb() ) );
    }

    return _instance;
}


bool Db::connectToDb()
{
    bool statusOk = _db->connectToDb();
    return statusOk;
}


bool Db::connectToDb( DbSettingData settingData )
{
    bool statusOk = _db->connectToDb( settingData );
    return statusOk;
}


QSharedPointer<DbSetting> Db::getSetting() const
{
    return _db->getSetting();
}


void Db::setSetting( DbSettingData settingData )
{
    _db->setSetting( settingData );
}


bool Db::query( QString query, QStringList &arguments )
{
    bool statusOk = _db->query( query, arguments );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    return statusOk;
}


bool Db::query( QString query )
{
    bool statusOk = _db->query( query );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    return statusOk;
}


QSharedPointer<QSqlQuery> Db::getData() const
{
    return _db->getData();
}


QSqlError Db::lastError() const
{
    return _db->lastError();
}


QVariant Db::lastInsertId() const
{
    return _db->lastInsertId();
}


void Db::logError(QString fileName, int line)
{
    auto lastError = _db->lastError();

    ErrorFileInfo errorFileInfo;
    errorFileInfo.setFileName( fileName );
    errorFileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , lastError.text()
                                , errorFileInfo );
}


QSharedPointer<Db> Db::_instance;
