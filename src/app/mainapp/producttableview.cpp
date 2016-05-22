#include "producttableview.h"

ProductTableView::ProductTableView( QWidget *parent ) :
    QTableView( parent )
{
    _productModel = QSharedPointer<ProductModel>( new ProductModel() );
}


void ProductTableView::setProductModel()
{
    auto model = _productModel->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( &*model );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
}


void ProductTableView::setProductModel( QString orderId )
{
    auto model = _productModel->getModel( orderId );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( &*model );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    int employeeName = 6;
    setColumnHidden( employeeName, true );
}


void ProductTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}
