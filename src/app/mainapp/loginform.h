#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QtWidgets>
#include "querytype.h"
#include "db.h"
#include "loginformerror.h"


namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm( QWidget *parent = 0 );
    ~LoginForm();

    QPushButton *getLoginButton();
    void message( QString text );
    void addSettingDbToForm();

public slots:
    void pressLoginButton();
    void saveSettings();

signals:
    void logInSuccessAsAdmin();
    void logInSuccessAsSeller();
    void changeSettings();

private:
    void initQueries();
    void initErrors();
    bool saveUserDataToApp();
    void logError( LoginFormError errorType, QString fileName, int line );
    void emitlogInSuccessSignal( bool isAdmin );

private:
    Ui::LoginForm *ui;
    QMap<QueryType, QString> _queries;
    QSharedPointer<Db> _db;
    QMap<LoginFormError, QString> _errors;

};

#endif // LOGINFORM_H
