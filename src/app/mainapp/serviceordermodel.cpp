#include "serviceordermodel.h"

ServiceOrderModel::ServiceOrderModel( QObject *parent ) :
    QObject( parent )
{
    _db = Db::getInstance();
    initQueries();
}


QString ServiceOrderModel::addOrder( QString customerId )
{
    QStringList parameters;
    parameters << qApp->property( "employeeId" ).toString()
               << customerId
               << QDate::currentDate().toString( QString( "yyyy-MM-dd" ) );
    qDebug() << "parameters" << parameters.at(1);

    bool statusOk = _db->query( _queries[ QueryType::ADD_SERVICE_ORDER ]
                                , parameters );

    if ( !statusOk ) {
        logError( _db->lastError().text(), __FILE__, __LINE__ );
        return -1;
    }

    return lastInsertId();
}


QString ServiceOrderModel::getOrderId()
{
    return _orderId;
}


QString ServiceOrderModel::lastInsertId()
{
    auto query = _db->getData();
    query->next();

    QString lastInsertId = query->value( 0 ).toString();
    _orderId = lastInsertId;

    return lastInsertId;
}


void ServiceOrderModel::initQueries()
{
    _queries[ QueryType::ADD_SERVICE_ORDER ] =
            "select addServiceOrder('%1', '%2', '%3')";
}


void ServiceOrderModel::logError( QString error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}
