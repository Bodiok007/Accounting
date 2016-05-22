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


void ProductTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}
