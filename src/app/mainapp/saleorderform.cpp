#include "saleorderform.h"
#include "ui_saleorderform.h"

SaleOrderForm::SaleOrderForm( QWidget *parent ) :
   QWidget( parent ),
   ui( new Ui::SaleOrderForm )
{
    ui->setupUi(this);
    setAttribute( Qt::WA_ShowModal );

    _productModel = QSharedPointer<ProductModel>( new ProductModel() );
    _addProductForm = QSharedPointer<AddProductForm>(
                      new AddProductForm( nullptr, _productModel ) );

    connect( ui->pushButtonAddProduct
             , SIGNAL( clicked( bool ) )
             , &*_addProductForm
             , SLOT( show() ) );

    connect( &*_addProductForm
             , SIGNAL( addProduct( Product & ) )
             , SLOT( addProduct( Product & ) ) );

    /*connect( ui->pushButtonSaveSaleOrder
             , SIGNAL( clicked( bool ) )
             , SLOT( addOrder() ) );*/
}


void SaleOrderForm::closeEvent( QCloseEvent *event )
{
    qDebug() << "Before emitClose SaleOrderForm";
    emitClose();
    qDebug() << "After emitClose SaleOrderForm";
    event->accept();
    /*QWidget::closeEvent( event );*/
    qDebug() << "After QWidget::closeEvent( event ); SaleOrderForm";
}


void SaleOrderForm::emitClose()
{
    emit closeSaleOrderForm();
}


void SaleOrderForm::addProduct( Product &product )
{
    _productList.append(product);
    addProductToForm();
}


void SaleOrderForm::addOrder()
{
    if ( _productList.empty() ) {
        message( "Немає товарів для збереження!" );
        return;
    }

    bool statusOk = _productModel->addProduct( _productList.last() );

    if ( !statusOk ) {
        message( "Помилка при збереженні товару" );
    }
}


void SaleOrderForm::addProductToForm()
{
    auto table = ui->tableViewProductOrder;
    Product &product = _productList.last();

    QVector<QTableWidgetItem*> items;

    items.push_back( new QTableWidgetItem( product.name ) );
    items.push_back( new QTableWidgetItem( product.barcode ) );
    items.push_back( new QTableWidgetItem( product.category ) );
    items.push_back( new QTableWidgetItem( product.count ) );
    items.push_back( new QTableWidgetItem( product.cost ) );

    int row = table->rowCount();
    table->insertRow(row);

    for ( int i = 0; i < items.size(); ++i ) {
        table->setItem( row, i, items[ i ] );
    }
}


void SaleOrderForm::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


SaleOrderForm::~SaleOrderForm()
{
    qDebug() << "Destroy SaleOrderForm";
    delete ui;
    qDebug() << "END Destroy SaleOrderForm";
}
