#include "editemployeeform.h"
#include "ui_editemployeeform.h"

EditEmployeeForm::EditEmployeeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserForm)
{
    ui->setupUi(this);
    setAttribute( Qt::WA_ShowModal );

    _userModel = QSharedPointer<UserModel>( new UserModel() );
    _changePasswordForm = QSharedPointer<ChangePasswordForm>(
                          new ChangePasswordForm( nullptr, _userModel ) );
    initErrors();
    connectSlots();
}


void EditEmployeeForm::setUserEditInfo( UserEditInfo &user )
{
    _user = user;

    addUserInfoToForm();
}


void EditEmployeeForm::addUserInfoToForm()
{
    ui->lineFirstName->setText( _user.firstName );
    ui->lineLastName->setText( _user.lastName );
    ui->lineLogin->setText( _user.login );
}


void EditEmployeeForm::connectSlots()
{
    connect( ui->pushButtonSaveEditEmployee
             , SIGNAL( clicked( bool ) )
             , SLOT( updateUser() ) );

    connect( ui->pushButtonChangePassword
             , SIGNAL( clicked( bool ) )
             , SLOT( showEditPasswordForm() ) );
}


void EditEmployeeForm::updateUser()
{
    setUserInfoFromForm();

    if ( isFieldsEmpty() ) {
        logError( Errors::EMPTY_FIELDS_ERROR, __FILE__, __LINE__);
        message( _errors[ Errors::EMPTY_FIELDS_ERROR ] );
        return;
    }

    bool statusOk = _userModel->updateUser( _user );

    if ( statusOk ) {
        message( _errors[ Errors::NO_ERRORR ] );
        hide();
        clearFields();
        emit updateEmployees();
    }
    else {
        logError( Errors::UPDATE_EMPLOYEE_ERROR, __FILE__, __LINE__);
        message( _errors[ Errors::UPDATE_EMPLOYEE_ERROR ] );
    }
}


void EditEmployeeForm::showEditPasswordForm()
{
    _changePasswordForm->setUserId( _user.userId );
    _changePasswordForm->show();
}


void EditEmployeeForm::setUserInfoFromForm()
{
    _user.firstName = ui->lineFirstName->text();
    _user.lastName = ui->lineLastName->text();
    _user.login = ui->lineLogin->text();
}


bool EditEmployeeForm::isFieldsEmpty()
{
    if ( _user.firstName.isEmpty()
         || _user.lastName.isEmpty()
         || _user.login.isEmpty() ) {
        return true;
    }

    return false;
}


void EditEmployeeForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        QString( tr( "Дані збережено!" ) );
    _errors[ Errors::EMPTY_FIELDS_ERROR ] =
        QString( tr( "Заповніть, будь ласка, всі поля!" ) );
    _errors[ Errors::UPDATE_EMPLOYEE_ERROR ] =
        QString( tr( "Помилка при збереженні даних користувача!" ) );
}


void EditEmployeeForm::clearFields()
{
    ui->lineFirstName->setText("");
    ui->lineLastName->setText("");
    ui->lineLogin->setText("");
}


void EditEmployeeForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void EditEmployeeForm::logError( Errors error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ error ]
                                , fileInfo );
}


EditEmployeeForm::~EditEmployeeForm()
{
    delete ui;
}
