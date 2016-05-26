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
}


void ShowServiceOrderView::initContextMenu()
{
    _contextMenu = QSharedPointer<QMenu>( new QMenu( this ) );

    QAction *printCheck =
        _contextMenu->addAction( tr( "Друкувати чек" ) );
    printCheck->setObjectName( "printCheck" );

    /*QAction *showProduct =
        _contextMenu->addAction( tr( "Показати склад замовлення" ) );
    showProduct->setObjectName( "showProductOrder" );*/

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
    if ( pAction->objectName() == "printCheck" ) {
        printCheck();
    }
    /*else if ( pAction->objectName() == "showProductOrder" ) {
        QString orderId = getCurrentOrderId();
        emit showSale( orderId );
    }*/
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
    auto model = _serviceModel->getModel( orderId );

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



