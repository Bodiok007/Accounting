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

    setCategories();
}


AddProductForm::~AddProductForm()
{
    delete ui;
}


void AddProductForm::setCategories()
{
    ui->comboBoxProductCategories->addItems( _productModel->getCategoryList() );
}
