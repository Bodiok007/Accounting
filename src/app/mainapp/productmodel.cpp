#include "productmodel.h"

ProductModel::ProductModel( QObject *parent )
    : QObject( parent )
{
    _db = Db::getInstance();
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );
    initQueries();
}


QSharedPointer<QSqlQueryModel> ProductModel::getModel()
{
    _model->setQuery( _queries[ QueryType::GET_PRODUCT ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


QSharedPointer<QSqlQueryModel> ProductModel::getModelSold()
{
    _model->setQuery( _queries[ QueryType::GET_SOLD_PRODUCT ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


QSharedPointer<QSqlQueryModel> ProductModel::getModelUnsold()
{
    _model->setQuery( _queries[ QueryType::GET_UNSOLD_PRODUCT ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


QSharedPointer<QSqlQueryModel> ProductModel::getModel( QString orderId )
{
    _model->setQuery( _queries[ QueryType::GET_PRODUCT_BY_ORDER_ID ]
                      .arg( orderId ) );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModelFromOrder();

    return _model;
}


QSharedPointer<QSqlQueryModel>
ProductModel::getModelByCategory( QString category )
{
    _model->setQuery( _queries[ QueryType::GET_SOLD_PRODUCT_BY_CATEGORY ]
                      .arg( category ) );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModelFromOrder();

    return _model;
}


QSharedPointer<QSqlQueryModel> ProductModel::getModelByCost( QString lowCost
                                                             , QString hightCost )
{
    _model->setQuery( _queries[ QueryType::GET_SOLD_PRODUCT_BY_COST ]
                      .arg( lowCost )
                      .arg( hightCost ) );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModelFromOrder();

    return _model;
}


QSharedPointer<QSqlQueryModel>
ProductModel::getModelByCategoryAndCost( QMap<QString, QString> &data )
{
    _model->setQuery( _queries[ QueryType::GET_SOLD_PRODUCT_BY_CATEGORY_AND_COST ]
                      .arg( data[ "category" ] )
                      .arg( data[ "lowCost" ] )
                      .arg( data[ "hightCost" ] ) );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModelFromOrder();

    return _model;
}


QSharedPointer<QSqlQueryModel> ProductModel::getModelByBarcode( QString barcode )
{
    _model->setQuery( _queries[ QueryType::GET_UNSOLD_PRODUCT_BY_BARCODE ]
                      .arg( barcode ) );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModelFromOrder();

    return _model;
}


void ProductModel::setHeadersToModel()
{
    QStringList headers;
    headers << tr( "Замовлення №" )
            << tr( "Назва продукту" )
            << tr( "Штрих-код" )
            << tr( "Категорія" )
            << tr( "Ціна" );qDebug() << "setHeadersToModel()";

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


void ProductModel::setHeadersToModelFromOrder()
{
    QStringList headers;
    headers << tr( "Замовлення №" )
            << tr( "Назва продукту" )
            << tr( "Штрих-код" )
            << tr( "Категорія" )
            << tr( "Ціна" ) ;

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


QString ProductModel::addProduct( Product &product )
{
    QStringList parameters;
    parameters << product.name
               << product.barcode
               << product.category
               << product.cost;

    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT ], parameters );

    if ( !statusOk ) {
        logError( _db->lastError().text(), __FILE__, __LINE__ );
        return "-1";
    }

    return lastInsertId();
}


QString ProductModel::lastInsertId()
{
    auto query = _db->getData();
    query->next();

    QString lastInsertId = query->value( 0 ).toString();

    return lastInsertId;
}


QMap<QString, QString> &ProductModel::getCategories() const
{
    bool statusOk = _db->query( _queries[ QueryType::GET_PRODUCT_CATEGORIES ] );

    if ( !statusOk ) {
        logError( _db->lastError().text(), __FILE__, __LINE__ );
        return _categories;
    }

    auto categories = _db->getData();

    while ( categories->next() ) {
        QString categoryID = categories->value( 0 ).toString();
        QString categoryName = categories->value( 1 ).toString();
        _categories[ categoryID ] = categoryName;
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
            "select addProduct('%1', '%2', '%3', '%4')";
    _queries[ QueryType::GET_PRODUCT_CATEGORIES ] =
            "call getProductCategories()";
    _queries[ QueryType::GET_PRODUCT ] =
            "call getProduct()";
    _queries[ QueryType::GET_PRODUCT_BY_ORDER_ID ] =
            "call getProductByOrderId('%1')";
    _queries[ QueryType::GET_SOLD_PRODUCT_BY_CATEGORY ] =
            "call getSoldProductByCategory('%1')";
    _queries[ QueryType::GET_SOLD_PRODUCT ] =
            "call getSoldProduct()";
    _queries[ QueryType::GET_SOLD_PRODUCT_BY_COST ] =
            "call getSoldProductByCost('%1', '%2')";
    _queries[ QueryType::GET_SOLD_PRODUCT_BY_CATEGORY_AND_COST ] =
            "call getSoldProductByCategoryAndCost('%1', '%2', '%3')";
    _queries[ QueryType::GET_UNSOLD_PRODUCT ] =
            "call getUnsoldProduct()";
    _queries[ QueryType::GET_UNSOLD_PRODUCT_BY_BARCODE ] =
            "call getUnsoldProductByBarcode('%1')";
}


void ProductModel::logError( QString error, QString fileName, int line ) const
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}
