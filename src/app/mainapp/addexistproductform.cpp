#include "addexistproductform.h"
#include "ui_addexistproductform.h"

AddExistProductForm::AddExistProductForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::AddExistProductForm )
{
    ui->setupUi( this );
    ui->tableExistProduct->setUnsoldProductModel();

    setAttribute( Qt::WA_ShowModal );

    connect( ui->pushButtonAddProduct
             , SIGNAL( clicked( bool ) )
             , SLOT( addSelectedProduct() ) );

    connect( ui->pushButtonSearch
             , SIGNAL( clicked( bool ) )
             , SLOT( searchProduct() ) );
}


void AddExistProductForm::addSelectedProduct()
{
    _product = ui->tableExistProduct->getSelectedProduct();
    if ( _product.productId.isEmpty() ) {
        message( tr( "Виберіть, будь ласка, продукт!" ) );
        return;
    }

    emit addProduct( _product );
}


void AddExistProductForm::searchProduct()
{
    QString barcode = ui->lineBarcode->text();
    if ( !barcode.isEmpty() ) {
        ui->tableExistProduct->setUnsoldProductModelByBarcode( barcode );
    }
    else {
        ui->tableExistProduct->setUnsoldProductModel();
    }
}


void AddExistProductForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


AddExistProductForm::~AddExistProductForm()
{
    delete ui;
}
