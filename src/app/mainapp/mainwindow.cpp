#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent ),
      ui( new Ui::MainWindow )
{
    ui->setupUi( this );

    connectSlots();
}


void MainWindow::connectSlots()
{
    connect( ui->pushButtonOut
             , SIGNAL( clicked( bool ) )
             , SLOT( emitClose() ) );

    connect( ui->pushButtonAddSale
             , SIGNAL( clicked( bool ) )
             , SLOT( showSaleOrderForm() ) );

    connect( ui->pushButtonShowProducts
             , SIGNAL( clicked( bool ) )
             , SLOT( showProductForm() ) );

    connect( ui->pushButtonShowProductOrders
             , SIGNAL( clicked( bool ) )
             , SLOT( showProductOrderForm() ) );
}


void MainWindow::closeEvent( QCloseEvent *event )
{
    emitClose();

    QMainWindow::closeEvent(event);
}


void MainWindow::emitClose()
{
    emit closeMainForm();
}


void MainWindow::createSaleOrderForm()
{
    _saleOrderForm = QSharedPointer<SaleOrderForm>( new SaleOrderForm() );

    connect( &*_saleOrderForm
             , SIGNAL( closeSaleOrderForm() )
             , SLOT( destroySaleOrderForm() ) );
}


void MainWindow::showSaleOrderForm()
{
    if ( _saleOrderForm.isNull() ) {
        createSaleOrderForm();
    }

    _saleOrderForm->show();
}


void MainWindow::destroySaleOrderForm()
{
    if ( !_saleOrderForm.isNull() ) {
        qDebug() << "before Destroy SaleOrder from destroySaleOrderForm";
        _saleOrderForm.clear();
        qDebug() << "after Destroy SaleOrder from destroySaleOrderForm";
    }
}


void MainWindow::createProductForm()
{
    _productForm = QSharedPointer<ProductForm>( new ProductForm() );
    _productForm->setProductModel();

    connect( &*_productForm
             , SIGNAL( closeProductForm() )
             , SLOT( destroyProductForm() ) );
}


void MainWindow::showProductForm()
{
    if ( _productForm.isNull() ) {
        createProductForm();
    } else {
        _productForm->setProductModel();
    }

    _productForm->show();
}


void MainWindow::createProductForm( QString orderId )
{
    _productForm = QSharedPointer<ProductForm>( new ProductForm() );
    _productForm->setProductModel( orderId );

    connect( &*_productForm
             , SIGNAL( closeProductForm() )
             , SLOT( destroyProductForm() ) );
}


void MainWindow::showProductForm( QString orderId )
{
    if ( _productForm.isNull() ) {
        createProductForm( orderId );
    } else {
        _productForm->setProductModel( orderId );
    }

    _productForm->show();
}


void MainWindow::destroyProductForm()
{
    if ( !_productForm.isNull() ) {
        _productForm.clear();
    }
}


void MainWindow::createProductOrderForm()
{
    _productOrderForm = QSharedPointer<ProductOrderForm>(
                        new ProductOrderForm() );

    connect( &*_productOrderForm
             , SIGNAL( closeProductOrderForm() )
             , SLOT( destroyProductOrderForm() ) );

    connect( &*_productOrderForm
             , SIGNAL( showProduct( QString ) )
             , SLOT( showProductForm( QString ) ) );
}


void MainWindow::showProductOrderForm()
{
    if ( _productOrderForm.isNull() ) {
        createProductOrderForm();
    }

    _productOrderForm->show();
}


void MainWindow::destroyProductOrderForm()
{
    if ( !_productOrderForm.isNull() ) {
        _productOrderForm.clear();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
