#include "sendmessageform.h"
#include "ui_sendmessageform.h"

SendMessageForm::SendMessageForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::SendMessageForm )
{
    ui->setupUi( this );

     _db = Db::getInstance();

    _sms = QSharedPointer<SmsManager>(
           new SmsManager( nullptr, new SmsClubService() ) );

    _messageModel = QSharedPointer<MessageModel>( new MessageModel() );

    _messageOperations = MessageOperations::NOTHING;

    initErrors();

    connect( ui->pushButtonSendMessage
             , SIGNAL( clicked( bool ) )
             , SLOT( sendMessage() ) );

    connect( _sms.data()
             , SIGNAL( responseMessageIdReady() )
             , SLOT( messageIdReady() ) );

    connect( _sms.data()
             , SIGNAL( errorRequest() )
             , SLOT( errorRequest() ) );

    connect( _sms.data()
             , SIGNAL( responseStatusReady() )
             , SLOT( statusReady() ) );
}


void SendMessageForm::setOrderId( QString orderId )
{
    _orderId = orderId;
}


void SendMessageForm::setReceiverNumber( QString receiverNumber )
{
    _receiverNumber = receiverNumber;
}


void SendMessageForm::sendMessage()
{
    _messageOperations = MessageOperations::ADD_NEW_MESSAGE;

    QString message = ui->plainMessageText->toPlainText();
    _sms->send( _receiverNumber, message );
}


void SendMessageForm::addMessageToDb( QString status )
{
    if ( _serviceMessageId.isEmpty()
         || status.isEmpty() ) {
        message( _errors[ Errors::SEND_MESSAGE_ERROR ] );
        return;
    }

    Message messageToSave;
    messageToSave.text = ui->plainMessageText->toPlainText();
    messageToSave.status = status;
    messageToSave.serviceMessageId = _serviceMessageId;

    qDebug() << status << _serviceMessageId << " orderId " << _orderId;

    bool statusOk = _messageModel->addMessage( messageToSave, _orderId );

    if ( !statusOk ) {
        message( _errors[ Errors::ADD_MESSAGE_TO_DB_ERROR ] );
        ui->plainMessageText->clear();
    }
    else {
        message( _errors[ Errors::NO_ERRORR ] );
        hide();
        ui->plainMessageText->clear();
        emit updateOrders();
    }
}


void SendMessageForm::initErrors()
{
    _errors[ Errors::NO_ERRORR ] =
        tr( "Операцію з sms успішно здійснено!" );
    _errors[ Errors::SEND_MESSAGE_ERROR ] =
        tr( "Помилка надсилання sms!" );
    _errors[ Errors::ADD_MESSAGE_TO_DB_ERROR ] =
        tr( "Помилка збереження повідомлення в базі даних!" );
}


void SendMessageForm::messageIdReady()
{
    _serviceMessageId = _sms->getLastMessageId();

    /*if ( _serviceMessageId == "0" ) {
        message( _errors[ Errors::SEND_MESSAGE_ERROR ] );
        return;
    }*/

    _sms->getStatusRequest( _serviceMessageId );
    qDebug() << "after status request";
}


void SendMessageForm::statusReady()
{
    QString status = _sms->getStatus();
    qDebug() << status;
    if ( _messageOperations == MessageOperations::ADD_NEW_MESSAGE ) {
        addMessageToDb( status );
    }
}


void SendMessageForm::errorRequest()
{
    message( _errors[ Errors::SEND_MESSAGE_ERROR ] );
}


void SendMessageForm::message( QString text )
{
    QMessageBox msgBox;
    msgBox.setText( text );
    msgBox.exec();
}


SendMessageForm::~SendMessageForm()
{
    delete ui;
}
