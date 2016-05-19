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


SaleOrderForm::~SaleOrderForm()
{
    qDebug() << "Destroy SaleOrderForm";
    delete ui;
}
