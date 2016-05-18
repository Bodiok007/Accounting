#include "addproductform.h"
#include "ui_addproductform.h"

AddProductForm::AddProductForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::AddProductForm )
{
    ui->setupUi( this );
}


AddProductForm::~AddProductForm()
{
    delete ui;
}
