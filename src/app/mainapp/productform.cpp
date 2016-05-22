#include "productform.h"
#include "ui_productform.h"

ProductForm::ProductForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ProductForm )
{
    ui->setupUi(this);
    ui->tableProducts->setProductModel();
}


void ProductForm::closeEvent(QCloseEvent *event)
{
    emit closeProductForm();
    QWidget::closeEvent( event );
}


ProductForm::~ProductForm()
{
    delete ui;
}
