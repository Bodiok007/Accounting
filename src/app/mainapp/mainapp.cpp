#include "mainapp.h"

MainApp::MainApp( QObject *parent ) : QObject( parent )
{
    _loginForm = QSharedPointer<LoginForm>( new LoginForm() );
    _loginForm->show();

    connect( &*_loginForm
             , SIGNAL( logInSuccessAsAdmin() )
             , SLOT( showAdminForm() ) );

    connect( &*_loginForm
             , SIGNAL( logInSuccessAsSeller() )
             , SLOT( showMainForm() ) );

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


void MainApp::createMainForm()
{
    _mainForm = QSharedPointer<MainWindow>( new MainWindow() );

    connect( &*_mainForm
             , SIGNAL( closeMainForm() )
             , SLOT( showLoginForm() ) );
    connect( &*_mainForm
             , SIGNAL( closeMainForm() )
             , SLOT( destroyMainForm() ) );

}


void MainApp::showMainForm()
{
    if ( _mainForm.isNull() ) {
        createMainForm();
    }

    _mainForm->show();
}


void MainApp::destroyMainForm()
{
    if ( !_mainForm.isNull() ) {
        _mainForm.clear();
    }
}


void MainApp::showLoginForm()
{
    _loginForm->show();
}
