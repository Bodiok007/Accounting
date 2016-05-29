#ifndef SMSSETTING_H
#define SMSSETTING_H

#include <smssettingdata.h>
#include <QMap>

class SmsSetting
{
public:
    enum class Errors
    {
        READ_ERROR,
        WRITE_ERROR
    };

    SmsSetting();

    bool saveSetting( SmsSettingData &&smsSettingData );
    SmsSettingData readSetting();

private:
    void initErrors();
    void logError( QString error, QString fileName, int line );

private:
    SmsSettingData _setting;
    QString _settingFile;
    QMap<Errors, QString> _errors;
};

#endif // SMSSETTING_H
