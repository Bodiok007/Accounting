#include "saleform.h"
#include "ui_saleform.h"

SaleForm::SaleForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ProductOrderForm )
{
    ui->setupUi( this );
    ui->tableProductOrder->setSaleModel();

    connect( ui->tableProductOrder
             , SIGNAL( showSale( QString ) )
             , SIGNAL( showSale( QString ) ) );
}


void SaleForm::closeEvent( QCloseEvent *event )
{
    emit closeProductOrderForm();
    QWidget::closeEvent( event );
}


SaleForm::~SaleForm()
{
    delete ui;
}
