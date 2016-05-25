#include "serviceform.h"
#include "ui_serviceform.h"

ServiceForm::ServiceForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ServiceForm )
{
    ui->setupUi( this );
}


ServiceForm::~ServiceForm()
{
    delete ui;
}
