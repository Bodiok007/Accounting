#include "messagemodel.h"

MessageModel::MessageModel( QObject *parent )
    : QObject( parent )
{
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );
}


QSharedPointer<QSqlQueryModel> MessageModel::getModel()
{
    QString getMessageQuery = "CALL getMessage()";

    _model->setQuery( getMessageQuery );

    if ( _model->lastError().isValid() ) {
        logError( __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
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


void MessageModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _model->lastError().text()
                                , fileInfo );
}
