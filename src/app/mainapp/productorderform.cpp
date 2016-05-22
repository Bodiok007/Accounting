#include "productorderform.h"
#include "ui_productorderform.h"

ProductOrderForm::ProductOrderForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ProductOrderForm )
{
    ui->setupUi( this );
    ui->tableProductOrder->setProductOrderModel();

    connect( ui->tableProductOrder
             , SIGNAL( showProduct( QString ) )
             , SIGNAL( showProduct( QString ) ) );
}


void ProductOrderForm::closeEvent( QCloseEvent *event )
{
    emit closeProductOrderForm();
    QWidget::closeEvent( event );
}


ProductOrderForm::~ProductOrderForm()
{
    delete ui;
}
