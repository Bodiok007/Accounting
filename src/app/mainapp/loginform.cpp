#include "loginform.h"
#include "ui_loginform.h"


LoginForm::LoginForm( QWidget *parent )
    : QWidget( parent ),
      ui( new Ui::LoginForm )
{
    ui->setupUi( this );
    _db = Db::getInstance();
    addSettingDbToForm();
    initQueries();
    initErrors();

    connect( getLoginButton(),
             SIGNAL( clicked( bool ) ),
             SLOT( pressLoginButton() ) );

    // save parameters
    connect( ui->buttonSaveSettings,
             SIGNAL( clicked( bool ) ),
             SLOT( saveSettings() ) );

    // reconnect to DB with new parameter
    connect( this,
             SIGNAL( changeSettings() ),
             &*Db::getInstance(),
             SLOT( connectToDb() ) );

    ui->toolBox->setCurrentIndex( 0 );
}


QPushButton *LoginForm::getLoginButton()
{
    return ui->buttonEnter;
}


void LoginForm::pressLoginButton()
{   
    QString login = ui->lineLogin->text().replace( " ", "" );
    QString password = ui->linePassword->text().replace( " ", "" );

    if ( login == "" || password == "" ) {
        logError( LoginFormError::EMPTY_LOGIN_OR_PASSWORD, __FILE__, __LINE__ );
        message( _errors[ LoginFormError::EMPTY_LOGIN_OR_PASSWORD ] );

        return;
    }

    bool isAdmin = ui->checkBoxAdmin->isChecked();
    QStringList parameters;
    parameters << login
               << password
               << (isAdmin ? "admin" : "seller");

    bool statusOk = _db->query( _queries[ QueryType::LOGIN ], parameters);
    if ( !statusOk ) {
        message( _errors[ LoginFormError::ERROR_QUERY ] );
        return;
    }

    if ( saveUserDataToApp() ) {
        emitlogInSuccessSignal( isAdmin );

        //this->hide();
    }
    else {
        logError( LoginFormError::USER_NOT_FOUND, __FILE__, __LINE__ );
        message( _errors[ LoginFormError::USER_NOT_FOUND ] );
    }

    ui->linePassword->setText( "" );
}


void LoginForm::emitlogInSuccessSignal( bool isAdmin )
{
    if ( isAdmin ) {
        emit logInSuccessAsAdmin();
    }
    else {
        emit logInSuccessAsSeller();
    }
}


bool LoginForm::saveUserDataToApp()
{
    auto data = _db->getData();
    if ( data->size() <= 0 ) {
        return false;
    }

    data->next();

    QString userId = data->value( 0 ).toString();
    qApp->setProperty( "userId", userId );
    QString userName = data->value( 1 ).toString();
    qApp->setProperty( "userName", userName );

    return true;
}


void LoginForm::logError( LoginFormError errorType, QString fileName, int line )
{
    ErrorFileInfo fileInfo;
    fileInfo.setFileName( fileName );
    fileInfo.setLine( line );

    Logger::getInstance()->log( ErrorType::ERRORR
                                , _errors[ errorType ]
                                , fileInfo );
}


void LoginForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void LoginForm::addSettingDbToForm()
{
    auto setting = Db::getInstance()->getSetting()->readSetting();
    ui->lineNameDB->setText( setting.databaseName );
    ui->lineNameUserDB->setText( setting.userName );
    ui->linePasswordUserDB->setText( setting.password );
    ui->lineHostDB->setText( setting.hostName );
}


void LoginForm::saveSettings()
{
    auto setting = _db->getSetting();

    DbSettingData data;
    data.databaseName = ui->lineNameDB->text();
    data.userName = ui->lineNameUserDB->text();
    data.password = ui->linePasswordUserDB->text();
    data.hostName = ui->lineHostDB->text();

    bool statusOk = setting->saveSetting( data );
    if ( statusOk ) {
        message( tr( "Налаштування збережено!" ) );
        emit changeSettings();
    }
    else {
        logError( LoginFormError::ERROR_SAVE_SETTING, __FILE__, __LINE__ );
        message( _errors[ LoginFormError::ERROR_SAVE_SETTING ] );
    }
}


void LoginForm::initQueries()
{
    _queries[ QueryType::LOGIN ] =
        "SELECT employee.employeeId, CONCAT( firstName, ' ', lastName )"
        " FROM employeerole"
        " INNER JOIN role"
            " ON employeerole.roleId = role.roleId"
        " INNER JOIN employee"
            " ON employeerole.employeeId = employee.employeeId"
        " WHERE employee.login = ?"
            " AND employee.password = ?"
        " AND role.name = ?";
}


void LoginForm::initErrors()
{
   _errors[ LoginFormError::ERROR_QUERY ] =
       QString( tr( "Помилка запиту до бази даних!" ) );
   _errors[ LoginFormError::EMPTY_LOGIN_OR_PASSWORD ] =
       QString( tr( "Заповніть, будь ласка, поля логіна та пароля!" ) );
   _errors[ LoginFormError::USER_NOT_FOUND ] =
       QString( tr( "Користувача з таким логіном і паролем не знайдено!" ) );
   _errors[ LoginFormError::ERROR_SAVE_SETTING ] =
       QString( tr( "Неможливо зберегти дані налаштувань!" ) );
}


LoginForm::~LoginForm()
{
    delete ui;
}
