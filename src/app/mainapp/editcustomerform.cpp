#include "editcustomerform.h"
#include "ui_editcustomerform.h"

EditCustomerForm::EditCustomerForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::EditCustomerForm )
{
    ui->setupUi( this );
    _customerModel = QSharedPointer<CustomerModel>( new CustomerModel() );

    setAttribute( Qt::WA_ShowModal );

    initErrors();

    connect( ui->pushButtonUpdateCustomer
             , SIGNAL( clicked( bool ) )
             , SLOT( updateCustomer() ) );
}


void EditCustomerForm::setCustomer( Customer customer )
{
    _customer = customer;
    addCustomerToForm();
}


void EditCustomerForm::addCustomerToForm()
{
    ui->lineFirstName->setText( _customer.firstName );
    ui->lineLastName->setText( _customer.lastName );
    ui->linePhone->setText( _customer.phone );
}


void EditCustomerForm::updateCustomer()
{
    _customer.firstName = ui->lineFirstName->text();
    _customer.lastName = ui->lineLastName->text();
    _customer.phone = ui->linePhone->text();

    if ( isFieldsEmpty() ) {
        logError( Errors::EMPTY_FIELDS_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::EMPTY_FIELDS_ERROR ] );
        return;
    }

    bool updateCustomerOk = _customerModel->updateCustomer( _customer );

    if ( !updateCustomerOk ) {
        logError( Errors::UPDATE_CUSTOMER_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::UPDATE_CUSTOMER_ERROR ] );
        return;
    }

    message( _errors[ Errors::NO_ERRORR ] );
    emit updateCustomers();
    clearFields();
    hide();
}


bool EditCustomerForm::isFieldsEmpty()
{
    if ( _customer.id.isEmpty()
         || _customer.firstName.isEmpty()
         || _customer.lastName.isEmpty()
         || _customer.phone.isEmpty() ) {
        return true;
    }

    return false;
}


void EditCustomerForm::clearFields()
{
    ui->lineFirstName->setText( "" );
    ui->lineLastName->setText( "" );
    ui->linePhone->setText( "" );
}


void EditCustomerForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        QString( tr( "Дані про клієнта успішно обновлено!" ) );
    _errors[ Errors::EMPTY_FIELDS_ERROR ] =
        QString( tr( "Заповніть, будь ласка, всі поля!" ) );
    _errors[ Errors::UPDATE_CUSTOMER_ERROR ] =
            QString( tr( "Помилка при додаванні клієнт!" ) );
}


void EditCustomerForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void EditCustomerForm::logError( Errors error
                                 , QString fileName
                                 , int line)
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ error ]
                                , fileInfo );
}


EditCustomerForm::~EditCustomerForm()
{
    delete ui;
}
