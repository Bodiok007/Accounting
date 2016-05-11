#include "loginform.h"
#include "ui_loginform.h"
#include "db.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(getLoginButton(),
            SIGNAL(clicked(bool)),
            SLOT(pressLoginButton())
           );

    // save parameters
    connect(ui->buttonSaveSettings,
            SIGNAL(clicked(bool)),
            SLOT(saveSettings())
           );

    // reconnect to DB with new parameter
    /*connect(this,
            SIGNAL(changeSettings()),
            DB::instance(),
            SLOT(connectToDB())
           );*/

    setSettingsDB();
    initQueries();

    ui->toolBox->setCurrentIndex(0);
}


QPushButton *LoginForm::getLoginButton()
{
    return ui->buttonEnter;
}


void LoginForm::pressLoginButton()
{
    /*QString login = ui->lineLogin->text().replace(" ", "");
    QString password = ui->linePassword->text().replace(" ", "");

    if (login == "" || password == "") {
        message("Заповніть, будь ласка, поля логіна та пароля!");
        return;
    }

    QString userName = "";
    if ((userName = DB::instance()->logIn(login, password)) == NULL) {
        message("Користувач не знайдений! "
                "Перевірте, будь ласка, логін та пароль!" + DB::instance()->lastError().isValid());
        return;
    }

    emit logged(userName);

    //this->hide();
    ui->linePassword->setText("");*/
}


void LoginForm::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


void LoginForm::setSettingsDB()
{
    auto settings = Db::getInstance()->getSetting()->readSetting();
    ui->lineNameDB->setText(settings.databaseName);
    ui->lineNameUserDB->setText(settings.userName);
    ui->linePasswordUserDB->setText(settings.password);
    ui->lineHostDB->setText(settings.hostName);
}


void LoginForm::saveSettings()
{
    auto setting = Db::getInstance()->getSetting();

    DbSettingData data;
    data.databaseName = ui->lineNameDB->text();
    data.userName = ui->lineNameUserDB->text();
    data.password = ui->linePasswordUserDB->text();
    data.hostName = ui->lineHostDB->text();

    bool statusOk = setting->saveSetting( data );
    if (statusOk) {
        emit changeSettings();
    }
    else {
        message( tr( "Неможливо зберегти дані налаштувань!" ) );
    }
    /*DB::instance()->getSettings()->writeSettings(
                                        ui->lineNameDB->text(),
                                        ui->lineNameUserDB->text(),
                                        ui->linePasswordUserDB->text(),
                                        ui->lineHostDB->text()
                                        );
    emit changeSettings();
    DB::instance()->connectToDB();*/
}


void LoginForm::initQueries()
{
    _queries[ QueryType::LOGIN ] =
        "SELECT firstName FROM employeerole"
        "INNER JOIN role"
            "ON employeerole.roleId = role.roleId"
        "INNER JOIN employee"
            "ON employeerole.employeeId = employee.employeeId"
        "WHERE employee.login = ?"
            "AND employee.password = ?"
        "AND role.name = ?";
}


LoginForm::~LoginForm()
{
    delete ui;
}

