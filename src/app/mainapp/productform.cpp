#include "productform.h"
#include "ui_productform.h"

ProductForm::ProductForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ProductForm )
{
    ui->setupUi(this);
    ui->tableProducts->setProductModel();
}

ProductForm::~ProductForm()
{
    delete ui;
}
