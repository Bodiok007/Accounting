#include "showserviceorderform.h"
#include "ui_showserviceorderform.h"

ShowServiceOrderForm::ShowServiceOrderForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ShowServiceOrderForm )
{
    ui->setupUi( this );

    _db = Db::getInstance();

    connect( ui->tableServiceOrders
             , SIGNAL( sendMessage( QString, QString ) )
             , SLOT( showSendMessageForm( QString, QString ) ) );

    connect( ui->tableServiceOrders
             , SIGNAL( showService( QString ) )
             , SIGNAL( showService( QString ) ) );
}


void ShowServiceOrderForm::closeEvent( QCloseEvent *event )
{
    emit closeShowServiceOrderForm();
    QWidget::closeEvent( event );
}


void ShowServiceOrderForm::showSendMessageForm( QString orderId
                                                , QString customerNumber )
{
    if ( _sendMessageForm.isNull() ) {
        createSendMessageForm();
    }

    _sendMessageForm->setOrderId( orderId );
    _sendMessageForm->setReceiverNumber( customerNumber );

    _sendMessageForm->show();
}


void ShowServiceOrderForm::updateOrders()
{
    ui->tableServiceOrders->setServiceOrderModel();
}


void ShowServiceOrderForm::createSendMessageForm()
{
    _sendMessageForm = QSharedPointer<SendMessageForm>(
                       new SendMessageForm() );

    connect( _sendMessageForm.data()
             , SIGNAL( updateOrders() )
             , SLOT( updateOrders() ) );
}


ShowServiceOrderForm::~ShowServiceOrderForm()
{
    delete ui;
}

