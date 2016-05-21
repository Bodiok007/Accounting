#include "productordermodel.h"

ProductOrderModel::ProductOrderModel( QObject *parent ) :
    QObject(parent)
{
    _db = Db::getInstance();
    _orderId = "";
    initQueries();
}


QString ProductOrderModel::addOrder()
{
    QStringList parameters;
    parameters << qApp->property( "employeeId" ).toString()
               << QDate::currentDate().toString( QString( "yyyy-MM-dd" ) );
    qDebug() << "parameters" << parameters.at(1);

    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT_ORDER ]
                                , parameters );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
        return -1;
    }

    return lastInsertId();
}


QString ProductOrderModel::getOrderId()
{
    return _orderId;
}


void ProductOrderModel::initQueries()
{
    _queries[ QueryType::ADD_PRODUCT_ORDER ] =
            "select addProductOrder('%1', '%2')";
}


QString ProductOrderModel::lastInsertId()
{
    auto query = _db->getData();
    query->next();

    QString lastInsertId = query->value( 0 ).toString();
    _orderId = lastInsertId;

    return lastInsertId;
}


void ProductOrderModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _db->lastError().text()
                                , fileInfo );
}

