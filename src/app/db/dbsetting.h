#ifndef DBSETTINGS_H
#define DBSETTINGS_H

#include "dbsettingdata.h"
#include "../log/logger.h"
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
    DbSettingData readSetting();

private:
    QSharedPointer<QIODevice> _settingFile;
    DbSettingData _setting;

private:
    const QString DB_SETTING_DIRECTORY = QString( QObject::tr( "dbSetting" ) );
    const QString DB_SETTING_FILE_PATH = DB_SETTING_DIRECTORY
                                       + QDir::separator()
                                       + QString( QObject::tr( "dbSetting.ini" ) );
private:
    QMap<DbSettingError, QString> _errorMessages;

private:
    void createSettingFolder();
    void checkSettingFolder();
    void setErrors();
    bool isFileWithSettingExists();
    void readSettingFromFile( QString *settings[], int numSetting );
    void writeSettingToFile( DbSettingData &dbSettingData );

    void message( QString message );
    void logError( DbSettingError error, QString fileName, int line );
};

#endif // DBSETTINGS_H
