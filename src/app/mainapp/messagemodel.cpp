#include "messagemodel.h"

MessageModel::MessageModel( QObject *parent )
    : QObject( parent )
{
    _db = Db::getInstance();
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );
    initQueries();
}


QSharedPointer<QSqlQueryModel> MessageModel::getModel()
{
    _model->setQuery( _queries[ QueryType::GET_MESSAGE ] );

    if ( _model->lastError().isValid() ) {
        logError( __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


bool MessageModel::addMessage( Message &message, QString orderId )
{
    QStringList arguments;
    arguments << orderId
              << message.serviceMessageId
              << message.text
              << message.status;

    bool statusOk = _db->query( _queries[ QueryType::ADD_MESSAGE ]
                                , arguments );

    return statusOk;
}


bool MessageModel::updateMessageStatus( QString messageId, QString status )
{
    QStringList parameters;
    parameters << messageId << status;

    bool statusOk =_db->query( _queries[ QueryType::UPDATE_MESSAGE_STATUS ]
                               , parameters );

    return statusOk;
}


void MessageModel::setHeadersToModel()
{
    QStringList headers;
    headers << tr( "Замовлення №" )
            << tr( "Повідомлення" )
            << tr( "Статус" );

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


void MessageModel::initQueries()
{
   _queries[ QueryType::GET_MESSAGE ] =
       "CALL getMessage()";
   _queries[ QueryType::ADD_MESSAGE ] =
       "call addMessage('%1', '%2', '%3', '%4')";
   _queries[ QueryType::UPDATE_MESSAGE_STATUS ] =
       "call updateMessageStatus('%1', '%2')";
}


void MessageModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _model->lastError().text()
                                , fileInfo );
}
