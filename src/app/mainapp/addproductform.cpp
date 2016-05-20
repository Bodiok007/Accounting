#include "addproductform.h"
#include "ui_addproductform.h"
#include <QDebug>

AddProductForm::AddProductForm( QWidget *parent
                                , QSharedPointer<ProductModel> productModel ) :
    QWidget( parent ),
    ui( new Ui::AddProductForm )
{
    ui->setupUi( this );
    _productModel = productModel;
    setAttribute( Qt::WA_ShowModal );

    addCategoriesToForm();

    connect( ui->pushButtonAddProduct
             , SIGNAL( clicked( bool ) )
             , SLOT( saveProduct() ) );
}


void AddProductForm::addCategoriesToForm()
{
    ui->comboBoxProductCategories->addItems( _productModel->getCategoryList() );
}


void AddProductForm::saveProduct()
{
    _product.name = ui->lineProductName->text();
    _product.barcode = ui->lineBarCode->text();
    _product.category = ui->comboBoxProductCategories->currentText();
    _product.count = ui->lineCount->text();
    _product.cost = ui->lineCost->text();

    if ( isEmpty() ) {
        message( tr( "Заповніть, будь ласка, всі поля!" ) );
        return;
    }

    emit addProduct( _product );
    clearFields();
    hide();
}


bool AddProductForm::isEmpty()
{
    if ( _product.name.isEmpty()
         || _product.barcode.isEmpty()
         || _product.category.isEmpty()
         || _product.count.isEmpty()
         || _product.cost.isEmpty()) {
        return true;
    }

    return false;
}


void AddProductForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void AddProductForm::clearFields()
{
    ui->lineProductName->setText( "" );
    ui->lineBarCode->setText( "" );
    ui->lineCount->setText( "" );
    ui->lineCost->setText( "" );
}


AddProductForm::~AddProductForm()
{
    delete ui;
}
