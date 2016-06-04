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

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}


void ProductTableView::setSoldProductModelByCategory( QString category )
{
    auto model = _productModel->getModelByCategory( category );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}


void ProductTableView::setSoldProductModelByCost( QString lowCost
                                                  , QString hightCost )
{
    auto model = _productModel->getModelByCost( lowCost, hightCost );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}


void ProductTableView::setSoldProductModelByCategoryAndCost(
        QMap<QString, QString> &data )
{
    auto model = _productModel->getModelByCategoryAndCost( data );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}

void ProductTableView::setUnsoldProductModelByBarcode( QString barcode )
{
    auto model = _productModel->getModelByBarcode( barcode );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}


void ProductTableView::setSoldProductModel()
{
    auto model = _productModel->getModelSold();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}


void ProductTableView::setUnsoldProductModel()
{
    auto model = _productModel->getModelUnsold();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( 1, QHeaderView::Stretch );
    setColumnHidden( 0, true );
}


void ProductTableView::setProductModel( QString orderId )
{
    auto model = _productModel->getModel( orderId );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні товарів!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );

    setColumnHidden( 0, true ); // orderId

    int count = 5;
    setColumnHidden( count, true );

    int employeeName = 6;
    setColumnHidden( employeeName, true );
}


void ProductTableView::setProductModel( QMap<QString, QString> &filter )
{
    int filterCount = filter.size();

    switch( filterCount )
    {
    case 1:
        break;
    }
}


Product ProductTableView::getSelectedProduct()
{
    int currentRow = selectionModel()->currentIndex().row();

    Product product;

    // 0 is hide column with Id
    QModelIndex index = model()->index( currentRow, 0 );
    product.productId = model()->data( index ).toString();
    product.name = index.sibling( currentRow, 1 ).data().toString();
    product.barcode = index.sibling( currentRow, 2 ).data().toString();
    product.category = index.sibling( currentRow, 3 ).data().toString();
    product.cost = index.sibling( currentRow, 4 ).data().toString();
    product.count = "1";

    return product;
}


void ProductTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}
