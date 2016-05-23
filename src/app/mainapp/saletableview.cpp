#include "saletableview.h"
#include "product.h"
#include "productcheck.h"

SaleTableView::SaleTableView( QWidget *parent ) :
    QTableView( parent )
{
    _productModel = QSharedPointer<ProductModel>(
                    new ProductModel() );

    _productOrderModel = QSharedPointer<SaleModel>(
                         new SaleModel() );

    _check = QSharedPointer<CheckManager>(
             new CheckManager( nullptr, new ProductCheck() ) );

    initContextMenu();
}


void SaleTableView::setSaleModel()
{
    auto model = _productOrderModel->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні замовлень для товарів!" ) );
        return;
    }

    this->setModel( &*model );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}


void SaleTableView::initContextMenu()
{
    _contextMenu = QSharedPointer<QMenu>( new QMenu( this ) );

    QAction *printCheck =
        _contextMenu->addAction( tr( "Друкувати чек" ) );
    printCheck->setObjectName( "printCheck" );

    QAction *showProduct =
        _contextMenu->addAction( tr( "Показати склад замовлення" ) );
    showProduct->setObjectName( "showProductOrder" );

    connect( &*_contextMenu,
             SIGNAL( triggered( QAction* ) ),
             SLOT( activateCotextMenu( QAction* ) ) );
}


void SaleTableView::activateCotextMenu( QAction *pAction )
{
    if ( pAction->objectName() == "printCheck" ) {
        printCheck();
    }
    else if ( pAction->objectName() == "showProductOrder" ) {
        QString orderId = getCurrentOrderId();
        emit showSale( orderId );
    }
}


void SaleTableView::contextMenuEvent( QContextMenuEvent *pe )
{
    _contextMenu->exec( pe->globalPos() );
}


void SaleTableView::printCheck()
{
    QString orderId = getCurrentOrderId();
    auto model = _productModel->getModel( orderId );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при друкуванні: "
                     "неможливо отримати дані про продукти замовлення!" ) );
        return;
    }

    QList<Product> _productList;
    Product product;

    QString employeeName = model->record( 0 ).value( "employeeName" ).toString();

    QStringList general;
    general << orderId << employeeName;

    for( int i = 0; i < model->rowCount(); ++i ) {
        product.name = model->record( i ).value( "productName" ).toString();
        product.count = model->record( i ).value( "productCount" ).toString();
        product.cost = model->record( i ).value( "cost" ).toString();

        _productList.append( product );
    }

    print( general, _productList );
}


void SaleTableView::print( QStringList &general, QList<Product> &productList )
{
    ProductCheckData mapContainer;
    mapContainer[ general ] = &productList;

    QVariant dataToCheck;
    dataToCheck.setValue( mapContainer );

    _check->create( dataToCheck );
    _check->print();
}


QString SaleTableView::getCurrentOrderId()
{
    int currentRow = selectionModel()->currentIndex().row();

    QModelIndex orderIdIndex = model()->index( currentRow, 0 );
    QString orderId = model()->data( orderIdIndex ).toString();

    return orderId;
}


void SaleTableView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}
