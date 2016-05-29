#include "messagesettingform.h"
#include "ui_messagesettingform.h"

MessageSettingForm::MessageSettingForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::MessageSettingForm )
{
    ui->setupUi(this);
    _sms = QSharedPointer<SmsManager>(
           new SmsManager( nullptr, new SmsClubService() ) );

    initErrors();

    connect( ui->pushButtonSaveSettings
             , SIGNAL( clicked( bool ) )
             , SLOT( saveSettings() ) );
}


void MessageSettingForm::addSettingToForm()
{
    auto setting = _sms->getSetting()->readSetting();

    ui->lineEditLogin->setText( setting.login );
    ui->lineEditPassword->setText( setting.password );
    ui->lineEditAlfaName->setText( setting.alfaName );
}


void MessageSettingForm::saveSettings()
{
    if ( isFieldsEmpty() ) {
        message( _errors[ Errors::FIELD_EMPTY ] );
        return;
    }

    SmsSettingData setting;
    setting.login = ui->lineEditLogin->text();
    setting.password = ui->lineEditPassword->text();
    setting.alfaName = ui->lineEditAlfaName->text();

    bool statusOk = _sms->setSetting( std::move( setting ) );
    if ( !statusOk ) {
        message( _errors[ Errors::SAVE_ERROR ] );
    }
    else {
        message( _errors[ Errors::NO_ERRORR ] );
    }
}


bool MessageSettingForm::isFieldsEmpty()
{
    if ( ui->lineEditLogin->text().isEmpty()
         || ui->lineEditPassword->text().isEmpty()
         || ui->lineEditAlfaName->text().isEmpty() ) {
        return true;
    }

    return false;
}


void MessageSettingForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        tr( "Налаштування успішно збережені!" );
    _errors[ Errors::FIELD_EMPTY ] =
        tr( "Заповніть, будь ласка, всі поля!" );
    _errors[ Errors::SAVE_ERROR ] =
        tr( "Помилка збереження налаштувань!" );
}


void MessageSettingForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


MessageSettingForm::~MessageSettingForm()
{
    delete ui;
}
