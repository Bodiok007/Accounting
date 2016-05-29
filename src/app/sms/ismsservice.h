#ifndef ISMSSERVICE_H
#define ISMSSERVICE_H

#include <QString>
#include <QSharedPointer>
#include <smssettingdata.h>
#include <smssetting.h>

class ISmsService
{
public:
    virtual ~ISmsService() {}

    virtual void send( QString receiverNumber, QString message ) = 0;
    virtual bool isValid() = 0;
    virtual QString getLastMessageId() = 0;

    virtual QString getStatus() = 0;
    virtual void getStatusRequest( QString messageId ) = 0;

    virtual QSharedPointer<SmsSetting> getSetting() const = 0;
    virtual bool setSetting( SmsSettingData &&settingData ) = 0;

signals:
    virtual void responseMessageIdReady() = 0;
    virtual void responseStatusReady() = 0;
    virtual void errorRequest() = 0;
};

Q_DECLARE_INTERFACE(ISmsService, "ISmsService")

#endif // ISMSSERVICE_H
