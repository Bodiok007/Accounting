#include "changepasswordform.h"
#include "ui_changepasswordform.h"

ChangePasswordForm::ChangePasswordForm( QWidget *parent
                                        , QSharedPointer<UserModel> model )
    : QWidget( parent ),
    ui( new Ui::ChangePasswordForm )
{
    ui->setupUi(this);
    setAttribute( Qt::WA_ShowModal );
    initErrors();
    _model = model;
    connectSlots();
}


void ChangePasswordForm::connectSlots()
{
    connect( ui->pushButtonSaveNewPassword
             , SIGNAL( clicked( bool ) )
             , SLOT( savePassword() ) );
}


void ChangePasswordForm::savePassword()
{
    QString password = ui->lineNewPassword->text();
    QString repeatPassword = ui->lineNewPassword->text();

    if ( password.isEmpty() || repeatPassword.isEmpty() ) {
        logError( Errors::EMPTY_FIELDS_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::EMPTY_FIELDS_ERROR ] );
        clearFields();
        return;
    }

    if ( password != repeatPassword ) {
        logError( Errors::PASSWORDS_NOT_EQUALS, __FILE__, __LINE__ );
        message( _errors[ Errors::PASSWORDS_NOT_EQUALS ] );
        clearFields();
        return;
    }

    QString hashPassword = getHashString( QCryptographicHash::Sha256, password );
    bool statusOk = _model->updatePassword( _userId, hashPassword );

    if( !statusOk ) {
        logError( Errors::UPDATE_PASSWORD_ERROR, __FILE__, __LINE__ );
        message( _errors[ Errors::UPDATE_PASSWORD_ERROR ] );
        clearFields();
        return;
    }

    message(_errors[ Errors::NO_ERRORR ] );
    clearFields();
    hide();
}


void ChangePasswordForm::setUserId(QString userId )
{
    _userId = userId;
}


void ChangePasswordForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        QString( tr( "Пароль успішно змінено!" ) );
    _errors[ Errors::EMPTY_FIELDS_ERROR ] =
        QString( tr( "Заповніть, будь ласка, всі поля!" ) );
    _errors[ Errors::PASSWORDS_NOT_EQUALS ] =
        QString( tr( "Паролі не співпадають!" ) );
    _errors[ Errors::UPDATE_PASSWORD_ERROR ] =
            QString( tr( "Помилка при збереженні палолю!" ) );
}


void ChangePasswordForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void ChangePasswordForm::logError( Errors error, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ error ]
                                , fileInfo );
}


QString ChangePasswordForm::getHashString(QCryptographicHash::Algorithm algorithm
                                          , QString inputString)
{
    QByteArray tempBytePassword( inputString.toStdString().c_str() );
    QString hashString = QString( QCryptographicHash::hash(
                                    tempBytePassword
                                    , algorithm ).toHex() );
    return hashString;
}


void ChangePasswordForm::clearFields()
{
   ui->lineNewPassword->setText("");
   ui->lineRepeatNewPassword->setText("");
}


ChangePasswordForm::~ChangePasswordForm()
{
    delete ui;
}





