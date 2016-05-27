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

    connectSlots();
}


void CustomerForm::connectSlots()
{
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

    connect( ui->tableCustomer
             , SIGNAL( editCustomer( Customer& ) )
             , SLOT( editCustomer( Customer& ) ) );
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


void CustomerForm::editCustomer( Customer &customer )
{
    if ( _editCustomerForm.isNull() ) {
        createEditCustomerForm();
    }

    _editCustomerForm->setCustomer( customer );
    _editCustomerForm->show();
}


void CustomerForm::createEditCustomerForm()
{
    _editCustomerForm = QSharedPointer<EditCustomerForm>(
                        new EditCustomerForm() );

    connect( _editCustomerForm.data()
             , SIGNAL( updateCustomers() )
             , SLOT( setCustomerModel() ) );
}


void CustomerForm::showEditCustomerForm()
{
    if ( _editCustomerForm.isNull() ) {
        createEditCustomerForm();
    }

    _editCustomerForm->show();
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
