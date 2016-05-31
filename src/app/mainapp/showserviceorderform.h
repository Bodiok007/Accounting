#ifndef SHOWSERVICEORDERFORM_H
#define SHOWSERVICEORDERFORM_H

#include <QtWidgets>
#include "smsmanager.h"
#include "sendmessageform.h"

namespace Ui {
class ShowServiceOrderForm;
}

class ShowServiceOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowServiceOrderForm( QWidget *parent = 0 );
    ~ShowServiceOrderForm();

signals:
    void closeShowServiceOrderForm();
    void showService( QString orderId );

protected:
    void closeEvent( QCloseEvent *event );

private slots:
    void showSendMessageForm( QString orderId , QString customerNumber );
    void updateOrders();

private:
    void createSendMessageForm();

private:
    Ui::ShowServiceOrderForm *ui;
    QSharedPointer<SmsManager> _sms;
    QSharedPointer<SendMessageForm> _sendMessageForm;
    QSharedPointer<Db> _db;
};

#endif // SHOWSERVICEORDERFORM_H
