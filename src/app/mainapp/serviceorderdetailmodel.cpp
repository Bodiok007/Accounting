#include "serviceorderdetailmodel.h"

ServiceOrderDetailModel::ServiceOrderDetailModel( QObject *parent ) :
    QObject( parent )
{
    _db = Db::getInstance();
    initQueries();
}

bool ServiceOrderDetailModel::addOrderDetail( QString orderId
                                              , QString serviceId )
{
    QStringList parameters;
    parameters << orderId
               << serviceId;

    bool statusOk = _db->query( _queries[ QueryType::ADD_SERVICE_ORDER_DETAIL ]
                                , parameters );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    return statusOk;
}


void ServiceOrderDetailModel::initQueries()
{
    _queries[ QueryType::ADD_SERVICE_ORDER_DETAIL ] =
            "call addServiceOrderDetail('%1', '%2')";
}


void ServiceOrderDetailModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _db->lastError().text()
                                , fileInfo );
}
