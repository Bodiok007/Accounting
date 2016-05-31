#include "addcustomerform.h"
#include "ui_addcustomerform.h"

AddCustomerForm::AddCustomerForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::AddCustomerForm )
{
    ui->setupUi( this );
    _customerModel = QSharedPointer<CustomerModel>( new CustomerModel() );

    setAttribute( Qt::WA_ShowModal );

    initErrors();

    connect( ui->pushButtonAddCustomer
             , SIGNAL( clicked( bool ) )
             , SLOT( addCustomer() ) );
}


void AddCustomerForm::addCustomer()
{
    Customer customer;
    customer.firstName = ui->lineFirstName->text();
    customer.lastName = ui->lineLastName->text();
    customer.phone = ui->linePhone->text();

    if ( isFieldsEmpty( customer ) ) {
        logError( Errors::EMPTY_FIELDS_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::EMPTY_FIELDS_ERROR ] );
        return;
    }

    bool addCustomerOk = _customerModel->addCustomer( customer );

    if ( !addCustomerOk ) {
        logError( Errors::ADD_CUSTOMER_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::ADD_CUSTOMER_ERROR ] );
        return;
    }

    message( _errors[ Errors::NO_ERRORR ] );
    emit updateCustomers();
    clearFields();
    hide();
}


bool AddCustomerForm::isFieldsEmpty( Customer &customer )
{
    if ( customer.firstName.isEmpty()
         || customer.lastName.isEmpty()
         || customer.phone.isEmpty() ) {
        return true;
    }

    return false;
}


void AddCustomerForm::clearFields()
{
    ui->lineFirstName->setText( "" );
    ui->lineLastName->setText( "" );
    ui->linePhone->setText( "" );
}


void AddCustomerForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        QString( tr( "Клієнт успішно доданий!" ) );
    _errors[ Errors::EMPTY_FIELDS_ERROR ] =
        QString( tr( "Заповніть, будь ласка, всі поля!" ) );
    _errors[ Errors::ADD_CUSTOMER_ERROR ] =
            QString( tr( "Помилка при додаванні клієнта!" ) );
}


void AddCustomerForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void AddCustomerForm::logError( Errors error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ error ]
                                , fileInfo );
}


AddCustomerForm::~AddCustomerForm()
{
    delete ui;
}
