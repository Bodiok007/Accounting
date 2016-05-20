#include "productorderdetailmodel.h"

ProductOrderDetailModel::ProductOrderDetailModel( QObject *parent ) :
    QObject( parent )
{
    _db = Db::getInstance();
    initQueries();
}


bool ProductOrderDetailModel::addOrderDetail( QString orderId
                                              , Product &product )
{
    QStringList parameters;
    parameters << orderId
               << product.productId
               << product.count;

    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT_ORDER_DETAIL ]
                                , parameters );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    return statusOk;
}


void ProductOrderDetailModel::initQueries()
{
    _queries[ QueryType::ADD_PRODUCT_ORDER_DETAIL ] =
            "call addProductOrderDetail('%1', '%2', '%3')";
}


void ProductOrderDetailModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _db->lastError().text()
                                , fileInfo );
}
