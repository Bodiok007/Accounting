#include "salemodel.h"

SaleModel::SaleModel( QObject *parent ) :
    QObject(parent)
{
    _db = Db::getInstance();
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );
    _orderId = "";
    initQueries();
}


QString SaleModel::addOrder()
{
    QStringList parameters;
    parameters << qApp->property( "employeeId" ).toString()
               << QDate::currentDate().toString( QString( "yyyy-MM-dd" ) );
    qDebug() << "parameters" << parameters.at(1);

    bool statusOk = _db->query( _queries[ QueryType::ADD_PRODUCT_ORDER ]
                                , parameters );

    if ( !statusOk ) {
        logError( _db->lastError().text(), __FILE__, __LINE__ );
        return -1;
    }

    return lastInsertId();
}


QString SaleModel::getOrderId()
{
    return _orderId;
}


QSharedPointer<QSqlQueryModel> SaleModel::getModel()
{
    _model->setQuery( _queries[ QueryType::GET_PRODUCT_ORDER ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


void SaleModel::setHeadersToModel()
{
    QStringList headers;
    headers << tr( "Замовлення №" )
            << tr( "Продавець" )
            << tr( "Дата замовлення" )
            << tr( "Кількість продуктів" )
            << tr( "Вартість замовлення" );

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


void SaleModel::initQueries()
{
    _queries[ QueryType::ADD_PRODUCT_ORDER ] =
            "select addProductOrder('%1', '%2')";
    _queries[ QueryType::GET_PRODUCT_ORDER ] =
            "call getSale()";
}


QString SaleModel::lastInsertId()
{
    auto query = _db->getData();
    query->next();

    QString lastInsertId = query->value( 0 ).toString();
    _orderId = lastInsertId;

    return lastInsertId;
}


void SaleModel::logError( QString error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}

