#include "employeetableview.h"

EmployeeTableView::EmployeeTableView( QWidget *parent )
    : QTableView( parent )
{
    _model = QSharedPointer<UserModel>( new UserModel() );
    initError();
    initContextMenu();
}


void EmployeeTableView::setEmployeeModel()
{
    auto model = _model->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні працівників!" ) );
        return;
    }
    this->setModel( &*model );
    this->setColumnHidden( 0, true );

    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 2, QHeaderView::Stretch );
}


void EmployeeTableView::contextMenuEvent(QContextMenuEvent *pe)
{
    _contextMenu->exec( pe->globalPos() );
}


void EmployeeTableView::initContextMenu()
{
    _contextMenu = QSharedPointer<QMenu>( new QMenu( this ) );

    QAction *addSales =
        _contextMenu->addAction( tr( "Додати роль адміністратора" ) );
    addSales->setObjectName( "addAdmin" );

    QAction *addService =
        _contextMenu->addAction( tr( "Видалити роль адміністратора" ) );
    addService->setObjectName( "removeAdmin" );

    connect( &*_contextMenu,
             SIGNAL( triggered( QAction* ) ),
             SLOT( activateCotextMenu( QAction* ) ) );
}


void EmployeeTableView::initError()
{
    _errors[ Errors::NO_ADD_ROLE_ERROR ] =
        QString( tr( "Роль успішно додана!" ) );
    _errors[ Errors::NO_REMOVE_ROLE_ERROR ] =
        QString( tr( "Роль успішно видалена!" ) );
    _errors[ Errors::ADD_ROLE_ERROR ] =
        QString( tr( "Неможливо додати роль!" ) );
    _errors[ Errors::REMOVE_ROLE_ERROR ] =
        QString( tr( "Неможливо видалити роль!" ) );
}


QString EmployeeTableView::getCurrentEmployeeId()
{
    int currentRow = selectionModel()->currentIndex().row();

    // 0 is hide column with Id
    QModelIndex currentIndex = model()->index( currentRow, 0 );
    QString currentEmployeeID = model()->data(currentIndex).toString();

    return currentEmployeeID;
}


void EmployeeTableView::activateCotextMenu( QAction *pAction )
{
    if ( pAction->objectName() == "addAdmin" ) {
        addAdminRoleToUser();
    }
    else if ( pAction->objectName() == "removeAdmin" ) {
        removeAdminRoleFromUser();
    }
}


void EmployeeTableView::addAdminRoleToUser()
{
     bool statusOk = _model->addRoleToUser( getCurrentEmployeeId(), "admin" );

     if ( statusOk ) {
         setEmployeeModel();
         message( _errors[ Errors::NO_ADD_ROLE_ERROR ] );
     }
     else {
        logError( Errors::ADD_ROLE_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::ADD_ROLE_ERROR ] );
     }
}


void EmployeeTableView::removeAdminRoleFromUser()
{
    bool statusOk = _model->removeRoleFromUser( getCurrentEmployeeId()
                                                , "admin" );

    if ( statusOk ) {
        setEmployeeModel();
        message( _errors[ Errors::NO_REMOVE_ROLE_ERROR ] );
    }
    else {
       logError( Errors::REMOVE_ROLE_ERROR, __FILE__, __LINE__ );
       message( _errors[ Errors::REMOVE_ROLE_ERROR ] );
    }
}


void EmployeeTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void EmployeeTableView::logError( Errors error
                                  , QString fileName
                                  , int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ error ]
                                , fileInfo );
}
