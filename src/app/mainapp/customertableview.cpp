#include "customertableview.h"

CustomerTableView::CustomerTableView( QWidget *parent ) :
    QTableView( parent )
{
    _customerModel = QSharedPointer<CustomerModel>( new CustomerModel() );
    initContextMenu();
}


void CustomerTableView::setCustomerModel()
{
    auto model = _customerModel->getModel();
    setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    hideColumn( 0 );
}


void CustomerTableView::setCustomerModelByPhone( QString phone )
{
    auto model = _customerModel->getModelByPhone( phone );
    setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}


QString CustomerTableView::getSelectedCustomerId()
{
    int currentRow = selectionModel()->currentIndex().row();

    // 0 is hide column with Id
    QModelIndex userIdIndex = model()->index( currentRow, 0 );
    QString customerId = model()->data( userIdIndex ).toString();

    return customerId;
}


QString CustomerTableView::getSelectedCustomerName()
{
    int currentRow = selectionModel()->currentIndex().row();

    // 0 is hide column with Id
    QModelIndex userIdIndex = model()->index( currentRow, 1 );
    QString customerName = model()->data( userIdIndex ).toString();

    return customerName;
}


void CustomerTableView::initContextMenu()
{
    _contextMenu = QSharedPointer<QMenu>( new QMenu( this ) );

    QAction *updateUser =
        _contextMenu->addAction( tr( "Редагувати замовника" ) );
    updateUser->setObjectName( "updateCustomer" );

    connect( _contextMenu.data(),
             SIGNAL( triggered( QAction* ) ),
             SLOT( activateCotextMenu( QAction* ) ) );
}


void CustomerTableView::contextMenuEvent( QContextMenuEvent *pe )
{
    _contextMenu->exec( pe->globalPos() );
}


void CustomerTableView::activateCotextMenu( QAction *pAction )
{    
    if ( pAction->objectName() != "updateCustomer" ) {
        return;
    }

    int currentRow = selectionModel()->currentIndex().row();

    // 0 is hide column with Id
    QModelIndex currentIndex = model()->index( currentRow, 0 );
    QString customerId = model()->data( currentIndex ).toString();

    currentIndex = model()->index( currentRow, 1 );
    QStringList customerName = model()->data( currentIndex ).toString()
                                                            .split( " " );

    currentIndex = model()->index( currentRow, 2 );
    QString customerPhone = model()->data( currentIndex ).toString();

    Customer customer;
    customer.id = customerId;
    customer.firstName = customerName.at( 0 );
    customer.lastName = customerName.at( 1 );
    customer.phone = customerPhone;

    emit editCustomer( customer );
}
