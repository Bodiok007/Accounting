#include "servicemodel.h"


ServiceModel::ServiceModel( QWidget *parent ) :
    QWidget( parent )
{
    _db = Db::getInstance();
    initQueries();
}


QSharedPointer<QSqlQueryModel> ServiceModel::getModel()
{
    _model->setQuery( _queries[ QueryType::GET_SERVICE_ORDER ] );

    if ( _model->lastError().isValid() ) {
        logError( _model->lastError().text(), __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


void ServiceModel::setHeadersToModel()
{

}


QMap<QString, QString> &ServiceModel::getCategories() const
{
    bool statusOk = _db->query( _queries[ QueryType::GET_SERVICE_CATEGORIES ] );

    if ( !statusOk ) {
        logError( _db->lastError().text(), __FILE__, __LINE__ );
        return _categories;
    }

    auto categories = _db->getData();

    while ( categories->next() ) {
        QString categoryID = categories->value( "serviceCategoryId" ).toString();
        QString categoryName = categories->value( "categoryName" ).toString();
        _categories[ categoryID ] = categoryName;
    }

    return _categories;
}


QStringList ServiceModel::getCategoryList()
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


QString ServiceModel::addService( Service &service )
{
    QStringList parameters;
    parameters << service.category
               << service.description
               << service.cost;

    bool statusOk = _db->query( _queries[ QueryType::ADD_SERVICE ], parameters );

    if ( !statusOk ) {
        logError( _db->lastError().text(), __FILE__, __LINE__ );
        return "-1";
    }

    return lastInsertId();
}


QString ServiceModel::lastInsertId()
{
    auto query = _db->getData();
    query->next();

    QString lastInsertId = query->value( 0 ).toString();

    return lastInsertId;
}


void ServiceModel::initQueries()
{
    _queries[ QueryType::GET_SERVICE_CATEGORIES ] =
            "call getServiceCategories()";
    _queries[ QueryType::ADD_SERVICE ] =
            "select addService('%1', '%2', '%3')";
}


void ServiceModel::logError( QString error, QString fileName, int line ) const
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , error
                                , fileInfo );
}
