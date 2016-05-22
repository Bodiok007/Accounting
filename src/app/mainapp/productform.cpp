#include "productform.h"
#include "ui_productform.h"

ProductForm::ProductForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ProductForm )
{
    ui->setupUi( this );
}


void ProductForm::closeEvent( QCloseEvent *event )
{
    emit closeProductForm();
    QWidget::closeEvent( event );
}


ProductForm::~ProductForm()
{
    delete ui;
}


void ProductForm::setProductModel()
{
    ui->tableProducts->setProductModel();
}


void ProductForm::setProductModel( QString orderId )
{
    ui->tableProducts->setProductModel( orderId );
}
