#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>
#include "loginform.h"
#include "adminform.h"
#include "mainwindow.h"

class MainApp : public QObject
{
    Q_OBJECT
public:
    explicit MainApp( QObject *parent = 0 );

signals:

public slots:

private:

private slots:
    void createAdminForm();
    void showAdminForm();
    void destroyAdminForm();

    void createMainForm();
    void showMainForm();
    void destroyMainForm();

    void showLoginForm();

private:
    QSharedPointer<LoginForm> _loginForm;
    QSharedPointer<AdminForm> _adminForm;
    QSharedPointer<MainWindow> _mainForm;
};

#endif // MAINAPP_H
