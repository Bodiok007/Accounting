#include "showserviceform.h"
#include "ui_showserviceform.h"

ShowServiceForm::ShowServiceForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ShowServiceForm )
{
    ui->setupUi( this );
    setServiceModel();
}


void ShowServiceForm::setServiceModel()
{
    ui->tableShowService->setServiceModel();
}


void ShowServiceForm::setServiceModel( QString orderId )
{
    ui->tableShowService->setServiceModel( orderId );
}


ShowServiceForm::~ShowServiceForm()
{
    delete ui;
}

