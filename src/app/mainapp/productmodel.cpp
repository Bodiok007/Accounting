#include "productmodel.h"

ProductModel::ProductModel( QObject *parent )
    : QObject( parent )
{
    _db = Db::getInstance();
    initQueries();
}


bool ProductModel::saveProduct( Product *product )
{
    QStringList parameters;
    parameters << product->name
               << product->cost
               << product->barcode;

    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT ], parameters );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    return statusOk;
}


void ProductModel::initQueries()
{
    _queries[ QueryType::ADD_PRODUCT ] =
            "call addProduct('%1', '%2', '%3')";
}


void ProductModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _db->lastError().text()
                                , fileInfo );
}
