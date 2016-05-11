#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QtWidgets>
#include "querytype.h"


namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

    QPushButton *getLoginButton();
    void message(QString text);

    void setSettingsDB();

public slots:
    void pressLoginButton();
    void saveSettings();

signals:
    void logged(QString userName);
    void changeSettings();

private:
    void initQueries();

private:
    Ui::LoginForm *ui;
    QMap<QueryType, QString> _queries;

};

#endif // LOGINFORM_H
