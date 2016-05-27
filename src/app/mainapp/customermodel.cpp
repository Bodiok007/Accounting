#include "customermodel.h"
#include "logger.h"

CustomerModel::CustomerModel( QObject *parent ) :
    QObject( parent )
{
    _db = Db::getInstance();
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );

    initQueries();
}


QSharedPointer<QSqlQueryModel> CustomerModel::getModel()
{
    _model->setQuery( _queries[ QueryType::GET_CUSTOMER ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


QSharedPointer<QSqlQueryModel> CustomerModel::getModelByPhone( QString phone )
{
    _model->setQuery( _queries[ QueryType::GET_CUSTOMER_BY_PHONE ].arg( phone ) );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


bool CustomerModel::addCustomer( Customer &customer )
{
    QStringList parameters;
    parameters << customer.firstName
               << customer.lastName
               << customer.phone;

    bool statusOk = _db->query( _queries[ QueryType::ADD_CUSTOMER ]
                                , parameters );

    if ( !statusOk ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );
        return false;
    }

    return true;
}


bool CustomerModel::updateCustomer( Customer &customer )
{
    QStringList parameters;
    parameters << customer.id
               << customer.firstName
               << customer.lastName
               << customer.phone;

    bool statusOk = _db->query( _queries[ QueryType::UPDATE_CUSTOMER ]
                                , parameters );

    if ( !statusOk ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );
        return false;
    }

    return true;
}


void CustomerModel::initQueries()
{
    _queries[ QueryType::GET_CUSTOMER ] =
            "call getCustomer()";
    _queries[ QueryType::GET_CUSTOMER_BY_PHONE ] =
            "call getCustomerByPhone('%1')";
    _queries[ QueryType::ADD_CUSTOMER ] =
            "call addCustomer('%1', '%2', '%3')";
    _queries[ QueryType::UPDATE_CUSTOMER ] =
            "call updateCustomer('%1', '%2', '%3', '%4')";
}


void CustomerModel::setHeadersToModel()
{
    QStringList headers;
    headers << tr( "Замовник" )
            << tr( "Телефон" );

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


void CustomerModel::setHeadersToModelWithList()
{
    QStringList headers;
    headers << tr( "Замовник" );

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


void CustomerModel::logError( QString error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}
