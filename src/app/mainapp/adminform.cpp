#include "adminform.h"
#include "ui_adminform.h"

AdminForm::AdminForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi( this );
    setEmployeeModel();
    setMessageModel();

    connectSlots();
}


void AdminForm::setEmployeeModel()
{
    ui->tableEmployee->setEmployeeModel();
}


void AdminForm::setMessageModel()
{
   ui->tableMessage->setMessageModel();
}


void AdminForm::connectSlots()
{
    connect( ui->tableEmployee
             , SIGNAL( editUser( UserEditInfo ) )
             , SLOT( editEmployee( UserEditInfo ) ) );

    connect( ui->pushButtonAddEmployee
             , SIGNAL( clicked( bool ) )
             , SLOT( addEmployee() ) );

    connect( ui->pushButtonOut
             , SIGNAL( clicked( bool ) )
             , SLOT( emitClose() ) );
}


void AdminForm::createEditEmployeeForm()
{
    _editEmployeeForm = QSharedPointer<EditEmployeeForm>(
                            new EditEmployeeForm() );

    connect( &*_editEmployeeForm
             , SIGNAL( updateEmployees() )
             , SLOT( setEmployeeModel() ) );
}


void AdminForm::createAddEmployeeForm()
{
    _addEmployeeForm = QSharedPointer<AddEmployeeForm>(
                            new AddEmployeeForm() );

    connect( &*_addEmployeeForm
             , SIGNAL( updateEmployees() )
             , SLOT( setEmployeeModel() ) );
}


void AdminForm::editEmployee( UserEditInfo user )
{
    if ( _editEmployeeForm.isNull() ) {
        createEditEmployeeForm();
    }

    _editEmployeeForm->setUserEditInfo( user );

    showEditEmployeeForm();
}


void AdminForm::addEmployee()
{
    showAddEmployeeForm();
}


void AdminForm::showEditEmployeeForm()
{
    if ( _editEmployeeForm.isNull() ) {
        createEditEmployeeForm();
    }

    _editEmployeeForm->show();
}


void AdminForm::showAddEmployeeForm()
{
    if ( _editEmployeeForm.isNull() ) {
        createAddEmployeeForm();
    }

    _addEmployeeForm->show();
}


void AdminForm::emitClose()
{
    emit closeAdminForm();
}


void AdminForm::closeEvent( QCloseEvent *event )
{
    emitClose();

    QWidget::closeEvent(event);
}


AdminForm::~AdminForm()
{
    delete ui;
}

