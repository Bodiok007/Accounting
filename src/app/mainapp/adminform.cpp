#include "adminform.h"
#include "ui_adminform.h"

AdminForm::AdminForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::AdminForm )
{
    ui->setupUi( this );
    setEmployeeModel();
    setMessageModel();
    setProductModel();

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


void AdminForm::setProductModel()
{
    ui->tableViewProducts->setUnsoldProductModel();
}


void AdminForm::connectSlots()
{
    connect( ui->tableEmployee
             , SIGNAL( editUser( UserEditInfo ) )
             , SLOT( editEmployee( UserEditInfo ) ) );

    connect( ui->pushButtonAddEmployee
             , SIGNAL( clicked( bool ) )
             , SLOT( addEmployee() ) );

    connect( ui->pushButtonSettings
             , SIGNAL( clicked( bool ) )
             , SLOT( showMessageSettingForm() ) );

    connect( ui->pushButtonOut
             , SIGNAL( clicked( bool ) )
             , SLOT( emitClose() ) );

    connect( ui->pushButtonAddProduct
             , SIGNAL( clicked( bool ) )
             , SLOT( showAddProductForm() ) );

    connect( ui->pushButtonEditProduct
             , SIGNAL( clicked( bool ) )
             , SLOT( showEditProductForm() ) );
}


void AdminForm::createEditEmployeeForm()
{
    _editEmployeeForm = QSharedPointer<EditEmployeeForm>(
                        new EditEmployeeForm() );

    connect( _editEmployeeForm.data()
             , SIGNAL( updateEmployees() )
             , SLOT( setEmployeeModel() ) );
}


void AdminForm::createAddEmployeeForm()
{
    _addEmployeeForm = QSharedPointer<AddEmployeeForm>(
                       new AddEmployeeForm() );

    connect( _addEmployeeForm.data()
             , SIGNAL( updateEmployees() )
             , SLOT( setEmployeeModel() ) );
}


void AdminForm::createMessageSettingForm()
{
    _messageSettingForm = QSharedPointer<MessageSettingForm>(
                          new MessageSettingForm() );
}


void AdminForm::createAddProductForm()
{
    if ( _productModel.isNull() ) {
        createProductModel();
    }

    _addProductForm = QSharedPointer<AddProductForm>(
                      new AddProductForm( nullptr, _productModel ) );

    connect( _addProductForm.data()
             , SIGNAL( addProduct( Product & ) )
             , SLOT( addProductToDb( Product & ) ) );
}


void AdminForm::createEditProductForm()
{
    if ( _productModel.isNull() ) {
        createProductModel();
    }

    _editProductForm = QSharedPointer<EditProductForm>(
                       new EditProductForm( nullptr, _productModel ) );

    connect( _editProductForm.data()
             , SIGNAL( updateProducts() )
             , SLOT( setProductModel() ) );
}


void AdminForm::createProductModel()
{
    _productModel = QSharedPointer<ProductModel>( new ProductModel() );
}


void AdminForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void AdminForm::addProductToDb( Product &product )
{
    QString productId = _productModel->addProduct( product );

    if ( productId != "-1" ) {
        setProductModel();
        message( tr( "Товар успішно доданий!" ) );
    }
    else {
        message( tr( "Помилка додавання товару!" ) );
    }
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


void AdminForm::showEditProductForm()
{
    if ( _editProductForm.isNull() ) {
        createEditProductForm();
    }

    Product product = ui->tableViewProducts->getSelectedProduct();
    if ( product.productId.isEmpty() ) {
        message( tr( "Виберіть товар для редагування!" ) );
        return;
    }

    _editProductForm->addProductToForm( product );

    _editProductForm->show();
}


void AdminForm::showAddEmployeeForm()
{
    if ( _editEmployeeForm.isNull() ) {
        createAddEmployeeForm();
    }

    _addEmployeeForm->show();
}


void AdminForm::showAddProductForm()
{
    if ( _addProductForm.isNull() ) {
        createAddProductForm();
    }

    _addProductForm->show();
}


void AdminForm::showMessageSettingForm()
{
    if ( _messageSettingForm.isNull() ) {
        createMessageSettingForm();
    }

    _messageSettingForm->addSettingToForm();
    _messageSettingForm->show();
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

