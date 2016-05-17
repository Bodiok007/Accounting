#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>
#include "loginform.h"
#include "adminform.h"

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

private:
    QSharedPointer<LoginForm> _loginForm;
    QSharedPointer<AdminForm> _adminForm;
};

#endif // MAINAPP_H
