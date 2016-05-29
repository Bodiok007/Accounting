#include "smssetting.h"
#include <QApplication>
#include <QDebug>
#include <QSettings>
#include "logger.h"

SmsSetting::SmsSetting()
{
    QString directory = QApplication::applicationDirPath() + "/smsSetting";
    _settingFile = directory + "/smsSettings.ini";

    initErrors();
}


bool SmsSetting::saveSetting( SmsSettingData &&smsSettingData )
{
    _setting = smsSettingData;

    QSettings settings(_settingFile, QSettings::IniFormat);
    settings.setValue( "login", smsSettingData.login );
    settings.setValue( "password", smsSettingData.password );
    settings.setValue( "alfaName", smsSettingData.alfaName );
    settings.sync();

    if ( settings.status() != QSettings::NoError ) {
        logError( _errors[ Errors::WRITE_ERROR ], __FILE__, __LINE__ );
        return false;
    }

    return true;
}


SmsSettingData SmsSetting::readSetting()
{
    QSettings settings( _settingFile, QSettings::IniFormat );
    _setting.login = settings.value( "login", "").toString();
    _setting.password = settings.value( "password", "" ).toString();
    _setting.alfaName = settings.value( "alfaName", "" ).toString();
    _setting.isError = false;

    #ifdef QT_DEBUG
      qDebug() << _setting.login;
      qDebug() << _setting.password;
      qDebug() << _setting.alfaName;
    #endif

    if ( settings.status() != QSettings::NoError ) {
        _setting.isError = true;
        logError( _errors[ Errors::READ_ERROR ], __FILE__, __LINE__ );
    }

    return _setting;
}


void SmsSetting::initErrors()
{
    _errors[ Errors::READ_ERROR ] =
        QObject::tr( "Помилка при читанні sms налаштувань!" );
    _errors[ Errors::WRITE_ERROR ] =
        QObject::tr( "Помилка при записі sms налаштувань!" );
}


void SmsSetting::logError( QString error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}
