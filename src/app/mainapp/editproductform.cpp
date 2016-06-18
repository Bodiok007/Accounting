#include "editproductform.h"
#include "ui_editproductform.h"

EditProductForm::EditProductForm( QWidget *parent
                                  , QSharedPointer<ProductModel> model ):
    QWidget( parent ),
    ui( new Ui::EditProductForm )
{
    ui->setupUi( this );

    _productModel = model;

    addCategoriesToForm();

    connect( ui->pushButtonSaveProduct
             , SIGNAL( clicked( bool ) )
             , SLOT( saveEditedProduct() ) );
}


void EditProductForm::addProductToForm( Product &product )
{
    _product.productId = product.productId;

    ui->lineProductName->setText( product.name );
    ui->lineBarCode->setText( product.barcode );
    ui->lineCost->setText( product.cost );
    ui->lineCount->setText( product.count );
    ui->comboBoxProductCategories->setCurrentText( product.category );
}


void EditProductForm::addCategoriesToForm()
{
    ui->comboBoxProductCategories->addItems( _productModel->getCategoryList() );
}


void EditProductForm::saveEditedProduct()
{
    setProductInfoFromForm();

    if ( isFieldEmpty() ) {
        message( tr( "Заповніть, будь ласка, всі поля!" ) );
        return;
    }

    bool statusOk = _productModel->updateProduct( _product );

    if ( statusOk ) {
        message( tr( "Товар успішно зредагований!" ) );
    }
    else {
        message( tr( "Не вдалося зредагувати товар!" ) );
        return;
    }

    emit updateProducts();
    clearFields();
    hide();
}


bool EditProductForm::isFieldEmpty()
{
    if ( _product.name.isEmpty()
         || _product.barcode.isEmpty()
         || _product.category.isEmpty()
         || _product.count.isEmpty()
         || _product.cost.isEmpty() ) {
        return true;
    }

    return false;
}


void EditProductForm::setProductInfoFromForm()
{
    _product.barcode = ui->lineBarCode->text();
    _product.category = ui->comboBoxProductCategories->currentText();
    _product.cost = ui->lineCost->text();
    _product.count = ui->lineCount->text();
    _product.name = ui->lineProductName->text();
}


void EditProductForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void EditProductForm::clearFields()
{
    ui->lineProductName->setText( "" );
    ui->lineBarCode->setText( "" );
    ui->lineCost->setText( "" );
    ui->lineCount->setText( "" );
}


EditProductForm::~EditProductForm()
{
    delete ui;
}
