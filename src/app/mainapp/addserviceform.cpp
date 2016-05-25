#include "addserviceform.h"
#include "ui_addserviceform.h"

AddServiceForm::AddServiceForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::AddServiceForm )
{
    ui->setupUi( this );

    initFields();

    ui->comboServiceCategory->addItems( _serviceModel->getCategoryList() );

    connect( ui->pushButtonAddService
             , SIGNAL( clicked( bool ) )
             , SLOT( saveService() ) );
}


void AddServiceForm::initFields()
{
    _serviceModel = QSharedPointer<ServiceModel>( new ServiceModel() );
}


void AddServiceForm::saveService()
{
    Service service;
    service.category = ui->comboServiceCategory->currentText();
    service.description = ui->lineServiceDescription->toPlainText();
    service.cost = ui->lineServiceSum->text();

    if ( isEmpty( service ) ) {
        message( tr( "Заповніть, будь ласка, всі поля!" ) );
        return;
    }

    emit addService( service );
    clearFields();
    hide();
}


bool AddServiceForm::isEmpty( Service &service )
{
    if ( service.category.isEmpty()
         || service.description.isEmpty()
         || service.cost.isEmpty() ) {
        return true;
    }

    return false;
}


void AddServiceForm::clearFields()
{
    ui->lineServiceDescription->setPlainText( "" );
    ui->lineServiceSum->setText( "" );
}


void AddServiceForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


AddServiceForm::~AddServiceForm()
{
    delete ui;
}

