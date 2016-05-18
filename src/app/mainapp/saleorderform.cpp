#include "saleorderform.h"
#include "ui_saleorderform.h"

SaleOrderForm::SaleOrderForm( QWidget *parent ) :
   QWidget( parent ),
   ui(new Ui::SaleOrderForm)
{
    ui->setupUi(this);
}


SaleOrderForm::~SaleOrderForm()
{
    delete ui;
}


void SaleOrderForm::closeEvent( QCloseEvent *event )
{
    emitClose();
}


void SaleOrderForm::emitClose()
{
    emit closeSaleOrderForm();
}
