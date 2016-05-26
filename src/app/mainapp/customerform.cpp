#include "customerform.h"
#include "ui_customerform.h"

CustomerForm::CustomerForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::CustomerForm )
{
    ui->setupUi( this );
    setCustomerModel();

    _addCustomerForm = QSharedPointer<AddCustomerForm>(
                       new AddCustomerForm() );

    connect( &*_addCustomerForm
             , SIGNAL( updateCustomers() )
             , SLOT( setCustomerModel() ) );

    connect( ui->pushButtonAddCustomer
             , SIGNAL( clicked( bool ) )
             , &*_addCustomerForm
             , SLOT( show() ) );

    connect( ui->pushButtonFind
             , SIGNAL( clicked( bool ) )
             , SLOT( findCustomerByPhone() ) );
}


void CustomerForm::setCustomerModel()
{
    ui->tableCustomer->setCustomerModel();
}


void CustomerForm::findCustomerByPhone()
{
    QString customerPhone = ui->linePhone->text();

    if ( customerPhone.isEmpty() ) {
        ui->tableCustomer->setCustomerModel();
    }
    else {
        ui->tableCustomer->setCustomerModelByPhone( customerPhone );
    }
}


void CustomerForm::closeEvent( QCloseEvent *event )
{
    emit closeCustomerForm();
    QWidget::closeEvent( event );
}


CustomerForm::~CustomerForm()
{
    delete ui;
}
