#include "dbsetting.h"
#include <QTextStream>
#include <QMessageBox>
#include "logger.h"
#include <QDebug>


/*!
 * \brief DbSetting::DbSetting
 */
DbSetting::DbSetting()
{
    _settingFile =
        QSharedPointer<QIODevice>( new QFile( DB_SETTING_FILE_PATH ) );

    setErrors();
    checkSettingFolder();
    readSetting();
}


void DbSetting::setErrors()
{
   _errorMessages[ DbSettingError::FileNotExists ] =
       QString( QObject::tr( "Файл " ) ) + QDir::currentPath()
       + QDir::separator() + DB_SETTING_FILE_PATH
       + QObject::tr( " не існує! Задайте налашування для підключення до бази даних!" );
   _errorMessages[ DbSettingError::FolderNotExists ] =
       QString( QObject::tr( "Папка " ) ) + QDir::currentPath()
       + QDir::separator() + DB_SETTING_DIRECTORY
       + QObject::tr( " не існує! Створення нової папки." );
   _errorMessages[ DbSettingError::ErrorOpenFileForReading ] =
       QString( QObject::tr( "Файл " ) ) + QDir::currentPath()
       + QDir::separator() + DB_SETTING_FILE_PATH
       + QObject::tr( " неможливо відкрити для читання!" );
   _errorMessages[ DbSettingError::ErrorOpenFileForWriting ] =
       QString( QObject::tr( "Файл " ) ) + QDir::currentPath()
       + QDir::separator() + DB_SETTING_FILE_PATH
       + QObject::tr( " неможливо відкрити для запису!" );
}


void DbSetting::checkSettingFolder()
{
    if ( !QFile::exists( DB_SETTING_DIRECTORY ) ) {
        createSettingFolder();
        logError( DbSettingError::FolderNotExists, __FILE__, __LINE__ );
    }
}


void DbSetting::createSettingFolder()
{
    QDir dir;
    dir.mkdir(DB_SETTING_DIRECTORY);
}


/*!
 * \brief DbSetting::saveSetting
 * \param dbSettingData
 * \return
 */
bool DbSetting::saveSetting( DbSettingData dbSettingData )
{
    if (!_settingFile->open( QIODevice::WriteOnly
                               | QIODevice::Text ) ) {
        message( _errorMessages[ DbSettingError::ErrorOpenFileForWriting ] );
        logError( DbSettingError::ErrorOpenFileForWriting, __FILE__, __LINE__ );

        return false;
    }

    writeSettingToFile( dbSettingData );
    _settingFile->close();

    readSetting();

    return true;
}


void DbSetting::writeSettingToFile( DbSettingData &dbSettingData )
{
    QTextStream out( &*_settingFile );
    out << "databaseName:" << dbSettingData.databaseName << "\n";
    out << "userName:" << dbSettingData.userName << "\n";
    out << "password:" << dbSettingData.password << "\n";
    out << "hostName:" << dbSettingData.hostName;
}


/*!
 * \brief DbSetting::readSetting
 * \return
 */
DbSettingData DbSetting::readSetting()
{
    if ( !isFileWithSettingExists() ) {
        _setting.error = DbSettingError::FileNotExists;
        logError( DbSettingError::FileNotExists, __FILE__, __LINE__ );

        return _setting;
    }

    if ( !_settingFile->open( QIODevice::ReadOnly
                              | QIODevice::Text ) ) {
        message( _errorMessages[ DbSettingError::ErrorOpenFileForReading ] );
        _setting.error = DbSettingError::ErrorOpenFileForReading;
        logError( DbSettingError::ErrorOpenFileForReading, __FILE__, __LINE__ );

        return _setting;
    }

    const int numSetting = 4;
    QString *settings[ numSetting ];
    settings[ 0 ] = &_setting.databaseName;
    settings[ 1 ] = &_setting.userName;
    settings[ 2 ] = &_setting.password;
    settings[ 3 ] = &_setting.hostName;

    readSettingFromFile( settings, numSetting );

    _settingFile->close();

    _setting.error = DbSettingError::NoError;

    return _setting;
}


bool DbSetting::isFileWithSettingExists()
{
    if ( !QFile::exists( DB_SETTING_FILE_PATH ) ) {
        message( _errorMessages[ DbSettingError::FileNotExists ] );
        return false;
    }

    return true;
}


void DbSetting::readSettingFromFile(QString *settings[], int numSetting )
{
    QTextStream in( &*_settingFile );
    QStringList parameterList;
    QString line = "";
    int settingValue = 1;

    for ( int setting = 0; setting < numSetting; ++setting ) {
        if ( !in.atEnd() ) {
            line = in.readLine();
            parameterList = line.split( ":" );
            *settings[ setting ] = parameterList.at( settingValue );
        }
    }
}


void DbSetting::message( QString message )
{
    QMessageBox msgBox;
    msgBox.setText( message );
    msgBox.exec();
}


void DbSetting::logError( DbSettingError error, QString fileName, int line )
{
    ErrorFileInfo errorInfo;
    errorInfo.setFileName( fileName );
    errorInfo.setLine( line );
    Logger::getInstance()->log( ErrorType::ERROR
                                , _errorMessages[ error ]
                                , errorInfo );
}
