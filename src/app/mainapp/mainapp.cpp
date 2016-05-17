#include "mainapp.h"

MainApp::MainApp( QObject *parent ) : QObject( parent )
{
    _loginForm = QSharedPointer<LoginForm>( new LoginForm() );
    _loginForm->show();

    connect( &*_loginForm
             , SIGNAL( logInSuccessAsAdmin() )
             , SLOT( showAdminForm() ) );

}


void MainApp::createAdminForm()
{
    _adminForm = QSharedPointer<AdminForm>( new AdminForm() );
    connect( &*_adminForm
             , SIGNAL( closeAdminForm() )
             , SLOT( destroyAdminForm() ) );
}


void MainApp::showAdminForm()
{
    if ( _adminForm.isNull() ) {
        createAdminForm();
    }

    _adminForm->show();
}


void MainApp::destroyAdminForm()
{
    if ( !_adminForm.isNull() ) {
        _adminForm.clear();
    }
}
