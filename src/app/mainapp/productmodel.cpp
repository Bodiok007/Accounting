#include "productmodel.h"

ProductModel::ProductModel( QObject *parent )
    : QObject( parent )
{
    _db = Db::getInstance();
    initQueries();
}


bool ProductModel::addProduct( Product &product )
{
    QStringList parameters;
    parameters << product.name
               << product.barcode
               << product.category
               << product.cost;

    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT ], parameters );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    return statusOk;
}


QMap<QString, QString> &ProductModel::getCategories() const
{
    bool statusOk = _db->query( _queries[ QueryType::GET_PRODUCT_CATEGORIES ] );

    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
        return _categories;
    }

    auto categories = _db->getData();

    while ( categories->next() ) {
        QString categoryName = categories->value( 0 ).toString();
        QString categoryID = categories->value( 1 ).toString();
        _categories[ categoryName ] = categoryID;
    }

    return _categories;
}


QStringList ProductModel::getCategoryList()
{
    if ( _categories.empty() ) {
        getCategories();
    }

    QStringList categories;

    QMapIterator<QString, QString> i( _categories );
    while ( i.hasNext() ) {
        i.next();
        categories << i.value();
    }

    return categories;
}


void ProductModel::initQueries()
{
    _queries[ QueryType::ADD_PRODUCT ] =
            "call addProduct('%1', '%2', '%3', '%4')";
    _queries[ QueryType::GET_PRODUCT_CATEGORIES ] =
            "call getProductCategories()";
}


void ProductModel::logError( QString fileName, int line ) const
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _db->lastError().text()
                                , fileInfo );
}
