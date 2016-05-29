#include "smsmanager.h"

SmsManager::SmsManager( QObject *parent, ISmsService *smsService ) :
    QObject( parent )
{
    _smsService = QSharedPointer<ISmsService>( smsService );

    connect( dynamic_cast<QObject*>( _smsService.data() )
             , SIGNAL( responseMessageIdReady() )
             , SIGNAL( responseMessageIdReady() ) );

    connect( dynamic_cast<QObject*>( _smsService.data() )
             , SIGNAL( responseStatusReady() )
             , SIGNAL( responseStatusReady() ) );

    connect( dynamic_cast<QObject*>( _smsService.data() )
             , SIGNAL( errorRequest() )
             , SIGNAL( errorRequest() ) );
}


void SmsManager::send( QString receiverNumber, QString message )
{
    _smsService->send( receiverNumber, message );
}


bool SmsManager::isValid()
{
    return _smsService->isValid();
}


QString SmsManager::getLastMessageId()
{
    return _smsService->getLastMessageId();
}


QString SmsManager::getStatus()
{
    return _smsService->getStatus();
}


void SmsManager::getStatusRequest( QString messageId )
{
    _smsService->getStatusRequest( messageId );
}


QSharedPointer<SmsSetting> SmsManager::getSetting() const
{
    return _smsService->getSetting();
}


bool SmsManager::setSetting( SmsSettingData &&settingData )
{
    return _smsService->setSetting( std::move( settingData ) );
}
