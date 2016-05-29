#ifndef SMSCLUBSERVICE_H
#define SMSCLUBSERVICE_H

#include "ismsservice.h"
#include "responceparser.h"
#include <QtNetwork>
#include <QUrl>

class SmsClubService : public QObject, public ISmsService
{
   Q_OBJECT
   Q_INTERFACES(ISmsService)

public:
    enum class Requests
    {
        SEND_MESSAGE,
        GET_STATUS
    };

    SmsClubService( QObject *parent = 0 );

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

private:
    void initFields();
    void initRequests();
    void createNetworkReply( QNetworkRequest &request );
    QByteArray getEncodedMessage( QString message );
    void setSslConfiguration( QNetworkRequest &request );
    void logError( QString error, QString fileName, int line );

private slots:
    void replyError( QNetworkReply::NetworkError error );
    //void readyRead();
    void readyReadSendMessage();
    void readyReadGetStatus();

private:
    QSharedPointer<SmsSetting> _setting;
    QSharedPointer<QNetworkAccessManager> _networkAccessManager;
    QSharedPointer<QNetworkReply> _networkReply;
    QSharedPointer<ResponseParser> _responceParser;
    QMap<Requests, QString> _requests;
    QString _lastResponse;
    bool _isValid;
};

#endif // SMSCLUBSERVICE_H
