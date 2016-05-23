#include "customertableview.h"

CustomerTableView::CustomerTableView( QWidget *parent ) :
    QTableView( parent )
{
    _customerModel = QSharedPointer<CustomerModel>( new CustomerModel() );
}


void CustomerTableView::setCustomerModel()
{
    auto model = _customerModel->getModel();
    setModel( &*model );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}
