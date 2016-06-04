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

    connect( ui->pushButtonSearch
             , SIGNAL( clicked( bool ) )
             , SLOT( search() ) );
}


void SaleForm::closeEvent( QCloseEvent *event )
{
    emit closeProductOrderForm();
    QWidget::closeEvent( event );
}


void SaleForm::setSaleModel()
{
    ui->tableProductOrder->setSaleModel();
}


void SaleForm::setSaleModel( QString orderId )
{
    ui->tableProductOrder->setSaleModel( orderId );
}


void SaleForm::setSaleModelBySellerName( QString sellerName )
{
    ui->tableProductOrder->setSaleModelBySellerName( sellerName );
}


void SaleForm::setSaleModelByDate()
{
    QString format = "yyyy-MM-dd";

    QString startDate =  ui->dateStart->date().toString( format );
    QString endDate =  ui->dateEnd->date().toString( format );

    ui->tableProductOrder->setSaleModelByDate( startDate, endDate );
}


void SaleForm::search()
{
    QString orderId = ui->lineOrderId->text();
    QString sellerName = ui->lineEmployeeName->text();
    bool isDateEnable = ui->checkBoxEnableDate->isChecked();

    if ( orderId.isEmpty() && sellerName.isEmpty() && !isDateEnable  ) {
        setSaleModel();
    }
    else if ( !orderId.isEmpty() ) {
        setSaleModel( orderId );
    }
    else if ( !sellerName.isEmpty() ) {
        setSaleModelBySellerName( sellerName );
    }
    else if ( isDateEnable ) {
        setSaleModelByDate();
    }
}


SaleForm::~SaleForm()
{
    delete ui;
}
