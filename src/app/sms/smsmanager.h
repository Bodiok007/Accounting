#ifndef SMSMANAGER_H
#define SMSMANAGER_H

#include <QObject>
#include <ismsservice.h>

class SmsManager : public QObject
{
    Q_OBJECT
public:
    explicit SmsManager( QObject *parent = 0, ISmsService *smsService = 0 );

    void send( QString receiverNumber, QString message );
    bool isValid();
    QString getLastMessageId();

    QString getStatus();
    void getStatusRequest( QString messageId );

    QSharedPointer<SmsSetting> getSetting() const;
    bool setSetting( SmsSettingData &&settingData );

signals:
    void responseMessageIdReady();
    void responseStatusReady();
    void errorRequest();

public slots:

private:
    QSharedPointer<ISmsService> _smsService;
};

#endif // SMSMANAGER_H
