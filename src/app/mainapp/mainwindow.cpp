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

    connect( &*_productForm
             , SIGNAL( closeProductForm() )
             , SLOT( destroyProductForm() ) );
}


void MainWindow::showProductForm()
{
    if ( _productForm.isNull() ) {
        createProductForm();
    }

    _productForm->show();
}


void MainWindow::destroyProductForm()
{
    if ( !_productForm.isNull() ) {
        _productForm.clear();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
