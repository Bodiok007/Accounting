#ifndef DBSETTINGS_H
#define DBSETTINGS_H

#include "dbsettingdata.h"
#include <QFile>
#include <QSharedPointer>
#include <QDir>
#include <QObject>
#include <QMap>


class DbSetting
{
public:
    DbSetting();

public:
    bool saveSetting( DbSettingData dbSettingData );

private:
    QSharedPointer<QIODevice> _settingFile;
    QString _databaseName;
    QString _userName;
    QString _password;
    QString _hostName;

private:
    const QString DB_SETTING_DIRECTORY = QString( QObject::tr( "dbSetting" ) );
    const QString DB_SETTING_FILE_PATH = DB_SETTING_DIRECTORY
                                       + QDir::separator()
                                       + QString( QObject::tr( "dbSetting.ini" ) );
private:
    enum class DbSettingErrors
    {
        FileNotExists,
        ErrorOpenFileForReading,
        ErrorOpenFileForWriting
    };

    QMap<DbSettingErrors, QString> _errorMessages;

private:
    void createSettingFolder();
    void checkSettingFolder();
    bool readSetting();
    void setErrors();
    bool isFileWithSettingExists();
    void readSettingFromFile( QString *settings[], int numSetting );
    void writeSettingToFile( DbSettingData &dbSettingData );

    void message( QString message );
};

#endif // DBSETTINGS_H
