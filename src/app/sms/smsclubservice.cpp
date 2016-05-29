#include "smsclubservice.h"
#include "logger.h"

SmsClubService::SmsClubService( QObject *parent ) :
    QObject( parent )
{
    initFields();
    initRequests();
    _isValid = false;
}


void SmsClubService::initFields()
{
    _setting = QSharedPointer<SmsSetting>( new SmsSetting() );

    _networkAccessManager = QSharedPointer<QNetworkAccessManager>(
                            new QNetworkAccessManager() );

    _responceParser = QSharedPointer<ResponseParser>( new ResponseParser() );
}


void SmsClubService::send( QString receiverNumber, QString message )
{
    _isValid = false;

    QByteArray encodedString = getEncodedMessage( message );
    QString emsg = encodedString.toBase64();

    auto settings = _setting->readSetting();

    QNetworkRequest request( _requests[ Requests::SEND_MESSAGE ]
                             .arg( settings.login )
                             .arg( settings.password )
                             .arg( settings.alfaName )
                             .arg( receiverNumber )
                             .arg( emsg ) );

    setSslConfiguration( request );
    createNetworkReply( request );

    connect( _networkReply.data()
             , SIGNAL( readyRead() )
             , SLOT( readyReadSendMessage() ) );

    connect( _networkReply.data()
             , SIGNAL( error( QNetworkReply::NetworkError ) )
             , SLOT( replyError( QNetworkReply::NetworkError ) ) );
}


void SmsClubService::getStatusRequest( QString messageId )
{
    auto settings = _setting->readSetting();
    QNetworkRequest request( _requests[ Requests::GET_STATUS ]
                             .arg( settings.login )
                             .arg( settings.password )
                             .arg( messageId ) );

    setSslConfiguration( request );
    createNetworkReply( request );

    connect( _networkReply.data()
             , SIGNAL( readyRead() )
             , SLOT( readyReadGetStatus() ) );

    connect( _networkReply.data()
             , SIGNAL( error( QNetworkReply::NetworkError ) )
             , SLOT( replyError( QNetworkReply::NetworkError ) ) );
}


void SmsClubService::setSslConfiguration( QNetworkRequest &request )
{
    QSslConfiguration config;
    config.setProtocol( QSsl::TlsV1_0 );
    request.setSslConfiguration( config );
}


void SmsClubService::createNetworkReply( QNetworkRequest &request )
{
    if ( !_networkReply.isNull() ) {
        _networkReply.clear();
    }

    _networkReply = QSharedPointer<QNetworkReply>(
                    _networkAccessManager->get( request ) );
}


bool SmsClubService::isValid()
{
    return _isValid;
}


QString SmsClubService::getLastMessageId()
{
    QString lastMessageId = _responceParser->getMessageId( _lastResponse );

    return lastMessageId;
}


QString SmsClubService::getStatus()
{
    QString status = _responceParser->getStatus( _lastResponse );

    return status;
}


void SmsClubService::initRequests()
{
    _requests[ Requests::SEND_MESSAGE ] =
        "https://gate.smsclub.mobi/http/httpsendsms.php?username=%1"
        "&password=%2&from=%3&to=%4&text=%5==";

    _requests[ Requests::GET_STATUS ] =
        "https://gate.smsclub.mobi/http/httpgetsmsstate.php?username=%1"
        "&password=%2&smscid=%3";
}


void SmsClubService::replyError( QNetworkReply::NetworkError error )
{
    _isValid = false;

    _lastResponse.clear();
    logError( _networkReply->errorString(), __FILE__, __LINE__ );

    emit errorRequest();
}


/*void SmsClubService::readyRead()
{
    QByteArray data = _networkReply->readAll();
    QString responce = QString::fromStdString( data.toStdString() );
    _lastResponse = responce;

    #ifdef QT_DEBUG
      qDebug() << responce;
    #endif

    _isValid = true;
    emit responseReady();
}*/


void SmsClubService::readyReadSendMessage()
{
    QByteArray data = _networkReply->readAll();
    QString responce = QString::fromStdString( data.toStdString() );
    _lastResponse = responce;

    #ifdef QT_DEBUG
      qDebug() << responce;
    #endif

    _isValid = true;
    emit responseMessageIdReady();
}


void SmsClubService::readyReadGetStatus()
{
    QByteArray data = _networkReply->readAll();
    QString responce = QString::fromStdString( data.toStdString() );
    _lastResponse = responce;

    #ifdef QT_DEBUG
      qDebug() << responce;
    #endif

    _isValid = true;
    emit responseStatusReady();
}


QByteArray SmsClubService::getEncodedMessage( QString message )
{
    QTextCodec *codec = QTextCodec::codecForName( "Windows-1251" );
    QByteArray encodedMessage = codec->fromUnicode( message );

    return encodedMessage;
}


QSharedPointer<SmsSetting> SmsClubService::getSetting() const
{
    return _setting;
}


bool SmsClubService::setSetting( SmsSettingData &&settingData )
{
    bool statusOk = _setting->saveSetting( std::move( settingData ) );
    return statusOk;
}


void SmsClubService::logError( QString error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}
