#include "messagemodel.h"

MessageModel::MessageModel( QObject *parent )
    : QObject( parent )
{
    _model = new QSqlQueryModel();
}


QSqlQueryModel *MessageModel::getModel()
{
    QString getMessageQuery =
        "SELECT po.productOrderId, msg.text, msg.status"
        " FROM message AS msg"
        " LEFT JOIN productorder AS po"
            " ON msg.messageId = po.messageId";

    _model->setQuery(getMessageQuery);

    if ( _model->lastError().isValid() ) {
        logError( __FILE__, __LINE__ );

        return _model;
    }

    return _model;
}


void MessageModel::setHeaderModelSales()
{
    QStringList headers;
    headers << tr( "Номер замовлення" )
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


MessageModel::~MessageModel()
{
    delete _model;
}
