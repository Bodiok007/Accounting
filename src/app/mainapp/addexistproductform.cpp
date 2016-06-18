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
    // if(ui->productCount > _product.count) error;
    if ( _product.productId.isEmpty() ) {
        message( tr( "Виберіть, будь ласка, продукт!" ) );
        return;
    }

    if ( _product.count.toInt() < ui->spinBoxCount->value() ) {
        message( "Недостатньо товарів для додавання! Максимальна кількість: "
                     +  _product.count );
        return;
    }

    _product.count = QString::number( ui->spinBoxCount->value() );

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


void AddExistProductForm::setRangeCountProduct()
{

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
