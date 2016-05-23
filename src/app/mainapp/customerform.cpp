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
}


void CustomerForm::setCustomerModel()
{
    ui->tableCustomer->setCustomerModel();
}


CustomerForm::~CustomerForm()
{
    delete ui;
}
