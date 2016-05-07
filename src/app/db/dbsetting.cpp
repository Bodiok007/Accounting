#include "dbsetting.h"
#include <QTextStream>
#include <QMessageBox>


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

        return _setting;
    }

    if ( !_settingFile->open( QIODevice::ReadOnly
                              | QIODevice::Text ) ) {
        message( _errorMessages[ DbSettingError::ErrorOpenFileForReading ] );
        _setting.error = DbSettingError::ErrorOpenFileForReading;

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
