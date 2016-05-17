#include "usermodel.h"

UserModel::UserModel( QObject *parent )
    : QObject( parent )
{
    _db = Db::getInstance();
    _model = QSharedPointer<QSqlQueryModel>( new QSqlQueryModel() );
    initQueries();
}


QMap<QString, QString> &UserModel::getRoles()
{
    if ( !_roles.empty() ) {
        return _roles;
    }

    bool statusOk = _db->query( _queries[ QueryType::GET_ROLES ] );
    if ( !statusOk ) {
        logError( __FILE__, __LINE__ );
    }

    setRoles();

    return _roles;
}


QStringList UserModel::getListRoles()
{
    if ( _roles.empty() ) {
        getRoles();
    }

    QStringList roles;

    QMapIterator<QString, QString> i( _roles );
    while ( i.hasNext() ) {
        i.next();
        roles << i.key();
    }

    return roles;
}


bool UserModel::addUser( UserInfo user )
{
    QStringList parameters;
    parameters << user.firstName
               << user.lastName
               << user.login
               << user.password
               << user.role;

    bool statusOk = _db->query( _queries[ QueryType::ADD_EMPLOYEE ]
                                , parameters );
    return statusOk;
}


QSharedPointer<QSqlQueryModel> UserModel::getModel()
{
    QString getMessageQuery = "CALL getEmployee()";

    _model->setQuery( getMessageQuery );

    if ( _model->lastError().isValid() ) {
        logError( __FILE__, __LINE__ );

        return _model;
    }

    setHeadersToModel();

    return _model;
}


void UserModel::setHeadersToModel()
{
    QStringList headers;
    headers << tr( "Номер працівника" )
            << tr( "Працівник" )
            << tr( "Логін" )
            << tr( "Ролі" );

    int countHeaders = headers.count();

    for ( int currentHeader = 0;
              currentHeader < countHeaders;
              ++currentHeader ) {

       _model->setHeaderData( currentHeader
                              , Qt::Horizontal
                              , headers.at( currentHeader ) );
    }
}


bool UserModel::addRoleToUser( QString userId, QString role )
{
    QStringList parameters;
    parameters << userId
               << role;

    bool statusOk = _db->query( _queries[ QueryType::ADD_ROLE_TO_EMPLOYEE ]
                                , parameters );
    return statusOk;
}


bool UserModel::removeRoleFromUser( QString userId, QString role )
{
    QStringList parameters;
    parameters << userId
               << role;

    bool statusOk = _db->query( _queries[ QueryType::REMOVE_ROLE_FROM_EMPLOYEE ]
                                , parameters );
    return statusOk;
}


bool UserModel::updateUser( UserEditInfo user )
{
    QStringList parameters;
    parameters << user.userId
               << user.firstName
               << user.lastName
               << user.login;

    bool statusOk = _db->query( _queries[ QueryType::UPDATE_USER ]
                                , parameters );
    return statusOk;
}


bool UserModel::updatePassword( QString userId, QString password )
{
    QStringList parameters;
    parameters << userId
               << password;

    bool statusOk = _db->query( _queries[ QueryType::UPDATE_PASSWORD ]
                                , parameters );
    return statusOk;
}


void UserModel::logError( QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _db->lastError().text()
                                , fileInfo );
}


void UserModel::setRoles()
{
    auto roles = _db->getData();
    QString roleId = "";
    QString roleName = "";

    while ( roles->next() ) {
        roleId = roles->value( 0 ).toString();
        roleName = roles->value( 1 ).toString();
        _roles[ roleName ] = roleId;
    }
}


void UserModel::initQueries()
{
    _queries[ QueryType::ADD_EMPLOYEE ] =
        "call addUser('%1', '%2', '%3', '%4', '%5')";
    _queries[ QueryType::ADD_ROLE_TO_EMPLOYEE ] =
        "call addRoleToUser('%1', '%2')";
    _queries[ QueryType::GET_ROLES ] =
        "SELECT roleId, name FROM role";
    _queries[ QueryType::REMOVE_ROLE_FROM_EMPLOYEE ] =
        "call removeRoleFromUser('%1', '%2')";
    _queries[ QueryType::UPDATE_USER ] =
        "call updateUser('%1', '%2', '%3', '%4')";
    _queries[ QueryType::UPDATE_PASSWORD ] =
        "call updatePassword('%1', '%2')";
}

