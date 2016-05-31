#ifndef SENDMESSAGEFORM_H
#define SENDMESSAGEFORM_H

#include <QtWidgets>
#include "smsmanager.h"
#include "smsclubservice.h"
#include "messagemodel.h"

namespace Ui {
class SendMessageForm;
}

class SendMessageForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        SEND_MESSAGE_ERROR,
        EMPTY_STATUS,
        ADD_MESSAGE_TO_DB_ERROR
    };

    enum class MessageOperations
    {
        NOTHING,
        ADD_NEW_MESSAGE,
        UPDATE_STATUS
    };

    explicit SendMessageForm( QWidget *parent = 0 );
    ~SendMessageForm();

    void setOrderId( QString orderId );
    void setReceiverNumber( QString receiverNumber );

signals:
    void updateOrders();

private slots:
    void sendMessage();
    void messageIdReady();
    void statusReady();
    void errorRequest();

private:
    void addMessageToDb( QString status );
    void initErrors();
    void message( QString text );

private:
    Ui::SendMessageForm *ui;
    QString _orderId;
    QString _serviceMessageId;
    QString _receiverNumber;
    QSharedPointer<SmsManager> _sms;
    MessageOperations _messageOperations;
    QSharedPointer<Db> _db;
    QSharedPointer<MessageModel> _messageModel;
    QMap<Errors, QString> _errors;
};

#endif // SENDMESSAGEFORM_H
