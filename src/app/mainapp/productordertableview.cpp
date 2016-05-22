#include "productordertableview.h"

ProductOrderTableView::ProductOrderTableView( QWidget *parent ) :
    QTableView( parent )
{
    _productOrderModel = QSharedPointer<ProductOrderModel>(
                         new ProductOrderModel() );
}


void ProductOrderTableView::setProductOrderModel()
{
    auto model = _productOrderModel->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні замовлень для товарів!" ) );
        return;
    }

    this->setModel( &*model );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}


void ProductOrderTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}
