#include "showserviceorderform.h"
#include "ui_showserviceorderform.h"

ShowServiceOrderForm::ShowServiceOrderForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ShowServiceOrderForm )
{
    ui->setupUi( this );
}


void ShowServiceOrderForm::closeEvent( QCloseEvent *event )
{
    emit closeShowServiceOrderForm();
    QWidget::closeEvent( event );
}


ShowServiceOrderForm::~ShowServiceOrderForm()
{
    delete ui;
}

