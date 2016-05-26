#include "serviceordermodel.h"

ServiceOrderModel::ServiceOrderModel( QObject *parent ) :
    QObject( parent )
{
    _db = Db::getInstance();
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );
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


QSharedPointer<QSqlQueryModel> ServiceOrderModel::getModel()
{
    _model->setQuery( _queries[ QueryType::GET_SERVICE_ORDER ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


void ServiceOrderModel::setHeadersToModel()
{
    QStringList headers;
    headers << tr( "Замовлення №" )
            << tr( "Працівник" )
            << tr( "Замовник" )
            << tr( "Номер замовника" )
            << tr( "SMS-повідомлення" )
            << tr( "SMS-статус" )
            << tr( "Дата замовлення" )
            << tr( "Дата виконання" )
            << tr( "Кількість послуг" )
            << tr( "Вартість" );

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
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
    _queries[ QueryType::GET_SERVICE_ORDER ] =
            "call getServiceOrder()";
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
