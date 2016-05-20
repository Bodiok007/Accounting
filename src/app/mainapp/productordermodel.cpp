#include "productordermodel.h"

ProductOrderModel::ProductOrderModel( QObject *parent ) :
    QObject(parent)
{
    _db = Db::getInstance();
}


int ProductOrderModel::addOrder()
{
    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT_ORDER ] );

    if ( !statusOk ) {
        return -1;
    }

    return _db->lastInsertId();
}


void ProductOrderModel::initQueries()
{
    _queries[ QueryType::ADD_PRODUCT_ORDER ] =
            "call addProductOrder('%1', '%2')";
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
