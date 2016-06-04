#include "saleorderform.h"
#include "ui_saleorderform.h"
#include "productcheck.h"

SaleOrderForm::SaleOrderForm( QWidget *parent ) :
   QWidget( parent ),
   ui( new Ui::SaleOrderForm )
{
    ui->setupUi(this);
    setAttribute( Qt::WA_ShowModal );

    initFields();
    initErrors();
    connectSlots();
}


void SaleOrderForm::initFields()
{
    _db = Db::getInstance();

    _productModel = QSharedPointer<ProductModel>( new ProductModel() );

    _addProductForm = QSharedPointer<AddProductForm>(
                      new AddProductForm( nullptr, _productModel ) );

    _addExistProductForm = QSharedPointer<AddExistProductForm>(
                           new AddExistProductForm() );

    _saleModel = QSharedPointer<SaleModel>(
                 new SaleModel() );

    _productOrderDetailModel = QSharedPointer<ProductOrderDetailModel>(
                               new ProductOrderDetailModel() );

    _check = QSharedPointer<CheckManager>(
             new CheckManager( nullptr, new ProductCheck() ) );
}


void SaleOrderForm::connectSlots()
{
    connect( ui->pushButtonAddProduct
             , SIGNAL( clicked( bool ) )
             , _addProductForm.data()
             , SLOT( show() ) );

    connect( _addProductForm.data()
             , SIGNAL( addProduct( Product & ) )
             , SLOT( addProduct( Product & ) ) );

    connect( ui->pushButtonAddExistProduct
             , SIGNAL( clicked( bool ) )
             , _addExistProductForm.data()
             , SLOT( show() ) );

    connect( _addExistProductForm.data()
             , SIGNAL( addProduct( Product & ) )
             , SLOT( addProduct( Product & ) ) );

    connect( ui->pushButtonSaveSaleOrder
             , SIGNAL( clicked( bool ) )
             , SLOT( addOrder() ) );
}

void SaleOrderForm::closeEvent( QCloseEvent *event )
{
    emitClose();
    event->accept();
    /*QWidget::closeEvent( event );*/
}


void SaleOrderForm::emitClose()
{
    emit closeSaleOrderForm();
}


void SaleOrderForm::addProduct( Product &product )
{
    _productList.append( product );
    addProductToForm();
}


void SaleOrderForm::addOrder()
{
    if ( _productList.empty() ) {
        message( _errors[ Errors::PRODUCT_LIST_EMPTY_FOR_SAVE ] );
        return;
    }

    bool transactionOk = _db->transaction();
    if ( !transactionOk ) {
        message( _errors[ Errors::ADD_ORDER_ERROR ] );
        return;
    }

    QString orderId = _saleModel->addOrder();
    if ( orderId.toInt() <= 0 ) {
        _db->rollback();
        message( _errors[ Errors::ADD_ORDER_ERROR ] );
        return;
    }

    QString productId = "-1";
    bool addOrderDatailOk = false;

    for ( Product &product : _productList ) {

        if ( product.productId.isEmpty() ) {
            productId = _productModel->addProduct( product );

            if ( productId.toInt() <= 0  ) {
                _db->rollback();
                 message( _errors[ Errors::ADD_ORDER_ERROR ] );
                return;
            }

            product.productId = productId;
        }

        addOrderDatailOk = _productOrderDetailModel->addOrderDetail( orderId
                                                                     , product );
        if ( !addOrderDatailOk ) {
            _db->rollback();
             message( _errors[ Errors::ADD_ORDER_ERROR ] );
            return;
        }
    }

    bool commitTransactionOk = _db->commit();
    if ( commitTransactionOk ) {
        if ( isPrintCheck() ) {
            printCheck();
        }
        emit closeSaleOrderForm();
    }
    else {
        _db->rollback();
        message( _errors[ Errors::ADD_ORDER_ERROR ] );
    }
}


bool SaleOrderForm::isPrintCheck()
{
    QMessageBox msgBox;
    msgBox.setText( tr("Замовлення успішно додане! Бажаєте надрукувати чек?") );
    msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel );
    msgBox.setDefaultButton( QMessageBox::Ok );

    int userChoose = msgBox.exec();

    if ( userChoose != QMessageBox::Ok ) {
        return false;
    }

    return true;
}


void SaleOrderForm::printCheck()
{
    if ( _productList.empty() ) {
        message( _errors[ Errors::PRODUCT_LIST_EMPTY_FOR_PRINT ] );
        return;
    }

    QString orderId = _saleModel->getOrderId();
    QString employeeName = qApp->property( "employeeName" ).toString();

    QStringList general;
    general << orderId << employeeName;

    ProductCheckData mapContainer;
    mapContainer[ general ] = &_productList;

    QVariant dataToCheck;
    dataToCheck.setValue( mapContainer );

    _check->create( dataToCheck );
    _check->print();
}


void SaleOrderForm::addProductToForm()
{
    auto table = ui->tableViewProductOrder;
    Product &product = _productList.last();

    QVector<QTableWidgetItem*> items;

    items.push_back( new QTableWidgetItem( product.name ) );
    items.push_back( new QTableWidgetItem( product.barcode ) );
    items.push_back( new QTableWidgetItem( product.category ) );
    items.push_back( new QTableWidgetItem( product.cost ) );

    int row = table->rowCount();
    table->insertRow( row );

    for ( int i = 0; i < items.size(); ++i ) {
        table->setItem( row, i, items[ i ] );
    }
}


void SaleOrderForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        QString( tr( "Замовлення успішно додано!" ) );

    _errors[ Errors::PRODUCT_LIST_EMPTY_FOR_SAVE ] =
        QString( tr( "Немає товарів для збереження!" ) );

    _errors[ Errors::PRODUCT_LIST_EMPTY_FOR_PRINT ] =
        QString( tr( "Немає товарів для друку чека!" ) );

    _errors[ Errors::ADD_ORDER_ERROR ] =
        QString( tr( "Помилка при додаванні замовлення!" ) );
}


void SaleOrderForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


SaleOrderForm::~SaleOrderForm()
{
    delete ui;
}
