#include "customertableview.h"

CustomerTableView::CustomerTableView( QWidget *parent ) :
    QTableView( parent )
{
    _customerModel = QSharedPointer<CustomerModel>( new CustomerModel() );
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
