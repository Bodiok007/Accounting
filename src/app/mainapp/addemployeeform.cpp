#include "addemployeeform.h"
#include "ui_addemployeeform.h"
#include <QMessageBox>

AddEmployeeForm::AddEmployeeForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::AddEmployeeForm )
{
    ui->setupUi( this );
    setAttribute( Qt::WA_ShowModal );

    _userModel = QSharedPointer<UserModel>( new UserModel() );

    setRoles();
    initErrors();
    connectSlots();
}


void AddEmployeeForm::setRoles()
{
    //QMap<QString, QString> &roles = _userModel->getRoles();
    QStringList roles = _userModel->getListRoles();
    ui->comboBoxRoles->addItems( roles );
}


void AddEmployeeForm::connectSlots()
{
    connect( ui->pushButtonAddUser
             , SIGNAL( clicked( bool ) )
             , SLOT( addEmployee() ) );
}


void AddEmployeeForm::addEmployee()
{
    QString password = ui->linePassword->text();
    QString repeatPassword = ui->lineRepeatPassword->text();

    if ( password != repeatPassword ) {
        logError( AddEmployeeFromError::PASSWORDS_NOT_EQUALS, __FILE__, __LINE__);
        message( _errors[ AddEmployeeFromError::PASSWORDS_NOT_EQUALS ] );
        clearPasswordFields();
        return;
    }

    UserInfo &employee = getEmployee();

    if ( isFieldsEmpty( employee ) ) {
        logError( AddEmployeeFromError::EMPTY_FIELDS_ERROR, __FILE__, __LINE__);
        message( _errors[ AddEmployeeFromError::EMPTY_FIELDS_ERROR ] );
        return;
    }


    bool statusOk = _userModel->addUser( employee );
    if ( !statusOk ) {
        logError( AddEmployeeFromError::ADD_EMPLOYEE_ERROR, __FILE__, __LINE__);
        message( _errors[ AddEmployeeFromError::ADD_EMPLOYEE_ERROR ] );
        clearFields();
        return;
    }

    message( _errors[ AddEmployeeFromError::NO_ERRORR ] );
    hide();
    clearFields();
    emit updateEmployees();
}


UserInfo AddEmployeeForm::getEmployee()
{
    UserInfo employee;
    employee.firstName = ui->lineFirstName->text();
    employee.lastName = ui->lineLastName->text();
    employee.login = ui->lineLogin->text();

    QString password = ui->linePassword->text();
    QString hashPassword = getHashString( QCryptographicHash::Sha256, password );

    employee.password = hashPassword;
    employee.role = ui->comboBoxRoles->currentText();

    return employee;
}


bool AddEmployeeForm::isFieldsEmpty( UserInfo &user )
{
    if ( user.firstName.isEmpty()
         || user.lastName.isEmpty()
         || user.login.isEmpty()
         || user.password.isEmpty()
         || user.role.isEmpty() ) {
        return true;
    }

    return false;
}


QString AddEmployeeForm::getHashString( QCryptographicHash::Algorithm algorithm
                                        , QString inputString )
{
    QByteArray tempBytePassword( inputString.toStdString().c_str() );
    QString hashString = QString( QCryptographicHash::hash(
                                    tempBytePassword
                                    , algorithm ).toHex() );
    return hashString;
}


void AddEmployeeForm::clearFields()
{
    ui->lineFirstName->setText("");
    ui->lineLastName->setText("");
    ui->lineLogin->setText("");
    clearPasswordFields();
}


void AddEmployeeForm::clearPasswordFields()
{
    ui->linePassword->setText("");
    ui->lineRepeatPassword->setText("");
}


void AddEmployeeForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void AddEmployeeForm::logError( AddEmployeeFromError error
                                , QString fileName
                                , int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ error ]
                                , fileInfo );
}


void AddEmployeeForm::initErrors()
{
    _errors[ AddEmployeeFromError::NO_ERRORR ] =
        QString( tr( "Працівник успішно доданий!" ) );
    _errors[ AddEmployeeFromError::PASSWORDS_NOT_EQUALS ] =
        QString( tr( "Паролі не співпадають!" ) );
    _errors[ AddEmployeeFromError::EMPTY_FIELDS_ERROR ] =
        QString( tr( "Заповніть, будь ласка, всі поля!" ) );
    _errors[ AddEmployeeFromError::ADD_EMPLOYEE_ERROR ] =
            QString( tr( "Помилка при додаванні працівника!" ) );
}


AddEmployeeForm::~AddEmployeeForm()
{
    delete ui;
}
