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
             , SLOT( showSaleForm() ) );

    connect( ui->pushButtonShowSales
             , SIGNAL( clicked( bool ) )
             , SLOT( showProductOrderForm() ) );

    connect( ui->pushButtonShowCustomers
             , SIGNAL( clicked( bool ) )
             , SLOT( showCustomerForm() ) );

    connect( ui->pushButtonAddOrder
             , SIGNAL( clicked( bool ) )
             , SLOT( showAddServiceOrderForm() ) );

    connect( ui->pushButtonShowServicesOrder
             , SIGNAL( clicked( bool ) )
             , SLOT( showShowServiceOrderForm() ) );

    connect( ui->pushButtonShowServices
             , SIGNAL( clicked( bool ) )
             , SLOT( showShowServiceForm() ) );
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


void MainWindow::showSaleForm()
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


void MainWindow::showSaleForm( QString orderId )
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
    _productOrderForm = QSharedPointer<SaleForm>(
                        new SaleForm() );

    connect( &*_productOrderForm
             , SIGNAL( closeProductOrderForm() )
             , SLOT( destroyProductOrderForm() ) );

    connect( &*_productOrderForm
             , SIGNAL( showSale( QString ) )
             , SLOT( showSaleForm( QString ) ) );
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


void MainWindow::createCustomerForm()
{
    _customerForm = QSharedPointer<CustomerForm>( new CustomerForm() );

    connect( &*_customerForm
             , SIGNAL( closeCustomerForm() )
             , SLOT( destroyCustomerForm() ) );
}


void MainWindow::showCustomerForm()
{
    if ( _customerForm.isNull() ) {
        createCustomerForm();
    }

    _customerForm->show();
}


void MainWindow::destroyCustomerForm()
{
    if ( !_customerForm.isNull() ) {
        _customerForm.clear();
    }
}


void MainWindow::createAddServiceOrderForm()
{
    _serviceOrderForm = QSharedPointer<ServiceOrderForm>(
                        new ServiceOrderForm() );

    connect( _serviceOrderForm.data()
             , SIGNAL( closeServiceOrderForm() )
             , SLOT( destroyAddServiceOrderForm() ) );
}


void MainWindow::showAddServiceOrderForm()
{
    if ( _serviceOrderForm.isNull() ) {
        createAddServiceOrderForm();
    }

    _serviceOrderForm->show();
}


void MainWindow::destroyAddServiceOrderForm()
{
    if ( !_serviceOrderForm.isNull() ) {
        _serviceOrderForm.clear();
    }
}


void MainWindow::createShowServiceOrderForm()
{
    _showServiceOrderForm = QSharedPointer<ShowServiceOrderForm>(
                            new ShowServiceOrderForm() );

    connect( _showServiceOrderForm.data()
             , SIGNAL( closeShowServiceOrderForm() )
             , SLOT( destroyShowServiceOrderForm() ) );

    connect( _showServiceOrderForm.data()
             , SIGNAL( showService( QString ) )
             , SLOT( showShowServiceForm( QString ) ) );
}


void MainWindow::showShowServiceOrderForm()
{
    if ( _showServiceOrderForm.isNull() ) {
        createShowServiceOrderForm();
    }

    _showServiceOrderForm->show();
}


void MainWindow::destroyShowServiceOrderForm()
{
    if ( !_showServiceOrderForm.isNull() ) {
        _showServiceOrderForm.clear();
    }
}


void MainWindow::createShowServiceForm()
{
    _showServiceForm = QSharedPointer<ShowServiceForm>(
                       new ShowServiceForm() );

    connect( _showServiceForm.data()
             , SIGNAL( closeShowServiceForm() )
             , SLOT( destroyShowServiceForm() ) );
}


void MainWindow::showShowServiceForm()
{
    if ( _showServiceForm.isNull() ) {
        createShowServiceForm();
    }
    else {
        _showServiceForm->setServiceModel();
    }

    _showServiceForm->show();
}


void MainWindow::createShowServiceForm( QString orderId )
{
    _showServiceForm = QSharedPointer<ShowServiceForm>(
                       new ShowServiceForm() );
    _showServiceForm->setServiceModel( orderId );

    connect( _showServiceForm.data()
             , SIGNAL( closeShowServiceForm() )
             , SLOT( destroyShowServiceForm() ) );
}


void MainWindow::showShowServiceForm( QString orderId )
{
    if ( _showServiceForm.isNull() ) {
        createShowServiceForm( orderId );
    }
    else {
        _showServiceForm->setServiceModel( orderId );
    }

    _showServiceForm->show();
}


void MainWindow::destroyShowServiceForm()
{
    if ( !_showServiceForm.isNull() ) {
        _showServiceForm.clear();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
