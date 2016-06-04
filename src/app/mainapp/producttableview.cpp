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


void ProductTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}
