#include "showserviceorderview.h"
#include "servicecheck.h"

ShowServiceOrderView::ShowServiceOrderView( QWidget *parent ) :
    QTableView( parent )
{
    initFields();
    initContextMenu();
    setServiceOrderModel();
}


void ShowServiceOrderView::initFields()
{
    _serviceOrderModel = QSharedPointer<ServiceOrderModel>(
                         new ServiceOrderModel() );

    _serviceModel = QSharedPointer<ServiceModel>( new ServiceModel() );

    _check = QSharedPointer<CheckManager>(
             new CheckManager( nullptr, new ServiceCheck() ) );

    _sms = QSharedPointer<SmsManager>(
           new SmsManager( nullptr, new SmsClubService() ) );

    _db = Db::getInstance();

    _messageModel = QSharedPointer<MessageModel>( new MessageModel() );

    connect( _sms.data()
             , SIGNAL( responseStatusReady() )
             , SLOT( statusReady() ) );

    connect( _sms.data()
             , SIGNAL( errorRequest() )
             , SLOT( errorRequest() ) );
}


void ShowServiceOrderView::initContextMenu()
{
    _contextMenu = QSharedPointer<QMenu>( new QMenu( this ) );

    QAction *printCheck =
        _contextMenu->addAction( tr( "Друкувати чек" ) );
    printCheck->setObjectName( "printCheck" );

    QAction *sendMessage =
        _contextMenu->addAction( tr( "Надіслати sms" ) );
    sendMessage->setObjectName( "sendMessage" );

    QAction *updateMessageStatus =
        _contextMenu->addAction( tr( "Оновити статус sms" ) );
    updateMessageStatus->setObjectName( "updateMessageStatus" );

    QAction *showService =
        _contextMenu->addAction( tr( "Показати склад замовлення" ) );
    showService->setObjectName( "showServiceOrder" );

    connect( _contextMenu.data(),
             SIGNAL( triggered( QAction* ) ),
             SLOT( activateCotextMenu(QAction*) ) );
}


void ShowServiceOrderView::contextMenuEvent( QContextMenuEvent *pe )
{
    _contextMenu->exec( pe->globalPos() );
}


void ShowServiceOrderView::activateCotextMenu( QAction *pAction )
{
    qDebug() << "actiivateCon";
    if ( pAction->objectName() == "printCheck" ) {
        printCheck();
    }
    else if ( pAction->objectName() == "sendMessage" ) {
        QString orderId = getCurrentOrderId();
        QString customerNumber = getCurrentCustomerNumber();
        emit sendMessage( orderId, customerNumber );
    }
    else if ( pAction->objectName() == "updateMessageStatus" ) {
        updateMessageStatus();
    }
    else if ( pAction->objectName() == "showServiceOrder" ) {
        QString orderId = getCurrentOrderId();
        emit showService( orderId );
    }
}


void ShowServiceOrderView::setServiceOrderModel()
{
    auto model = _serviceOrderModel->getModel();

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при завантаженні послуг!" ) );
        return;
    }

    this->setModel( model.data() );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::ResizeToContents );
    horizontalHeader()->setSectionResizeMode( 9, QHeaderView::ResizeToContents );
    horizontalHeader()->hideSection( 10 ); // service message id
    horizontalHeader()->hideSection( 11 ); // local db message id
}


void ShowServiceOrderView::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


void ShowServiceOrderView::printCheck()
{
    qDebug() << "print check";
    QString orderId = getCurrentOrderId();
    auto model = _serviceModel->getModelForCheck( orderId );

    if ( model->lastError().isValid() ) {
        message( tr( "Помилка при друкуванні: "
                     "неможливо отримати дані про продукти замовлення!" ) );
        return;
    }

    QList<Service> serviceList;
    Service service;

    QString employeeName = model->record( 0 ).value( "employeeName" ).toString();
    QString customerName = model->record( 0 ).value( "customerName" ).toString();

    QStringList general;
    general << orderId << employeeName << customerName;

    for( int i = 0; i < model->rowCount(); ++i ) {
        service.description = model->record( i ).value( "description" )
                                                .toString();
        service.cost = model->record( i ).value( "cost" ).toString();

        serviceList.append( service );
    }

    print( general, serviceList );
}


void ShowServiceOrderView::print( QStringList &general
                                  , QList<Service> &serviceList )
{
    ServiceCheckData mapContainer;
    mapContainer[ general ] = &serviceList;

    QVariant dataToCheck;
    dataToCheck.setValue( mapContainer );

    _check->create( dataToCheck );
    _check->print();
}


QString ShowServiceOrderView::getCurrentOrderId()
{
    int currentRow = selectionModel()->currentIndex().row();

    QModelIndex orderIdIndex = model()->index( currentRow, 0 );
    QString orderId = model()->data( orderIdIndex ).toString();

    return orderId;
}


QString ShowServiceOrderView::getCurrentCustomerNumber()
{
    int currentRow = selectionModel()->currentIndex().row();

    QModelIndex orderIdIndex = model()->index( currentRow, 3 );
    QString customerNumber = model()->data( orderIdIndex ).toString();

    return customerNumber;
}


QString ShowServiceOrderView::getCurrentMessageId()
{
    int currentRow = selectionModel()->currentIndex().row();

    QModelIndex messageIdIndex = model()->index( currentRow, 11 );
    QString messageId = model()->data( messageIdIndex ).toString();

    return messageId;
}


QString ShowServiceOrderView::getCurrentServiceMessageId()
{
    int currentRow = selectionModel()->currentIndex().row();

    QModelIndex messageIdIndex = model()->index( currentRow, 10 );
    QString messageId = model()->data( messageIdIndex ).toString();

    return messageId;
}


void ShowServiceOrderView::updateMessageStatus()
{
    QString serviceMessageId = getCurrentServiceMessageId();

    _sms->getStatusRequest( serviceMessageId );
}


void ShowServiceOrderView::statusReady()
{
    QString messageId = getCurrentMessageId();
    QString status = _sms->getStatus();

    bool statusOk = _messageModel->updateMessageStatus( messageId, status );

    if ( !statusOk ) {
        message( tr( "Помилка оновленння статусу повідомлення!" ) );
    }
    else {
        setServiceOrderModel();
        message( tr( "Статус повідомлення успішно оновлений!" ) );
    }
}


void ShowServiceOrderView::errorRequest()
{
    qDebug() << "error request";
}
