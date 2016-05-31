#ifndef SHOWSERVICEORDERVIEW_H
#define SHOWSERVICEORDERVIEW_H

#include <QtWidgets>
#include "serviceordermodel.h"
#include "servicemodel.h"
#include "checkmanager.h"
#include "smsmanager.h"
#include "smsclubservice.h"
#include "messagemodel.h"

class ShowServiceOrderView : public QTableView
{
    Q_OBJECT

public:
    ShowServiceOrderView( QWidget *parent = 0 );

    void setServiceOrderModel();

signals:
    void sendMessage( QString orderId, QString customerNumber );
    void updateMessageStatus( QString orderId
                              , QString customerNumber
                              , QString messageId );
    void showService( QString orderId );

protected:
    void contextMenuEvent( QContextMenuEvent *pe );

private:
    void initFields();
    void initContextMenu();
    void message( QString text );

    void printCheck();
    void print( QStringList &general
                , QList<Service> &serviceList );

    QString getCurrentOrderId();
    QString getCurrentCustomerNumber();
    QString getCurrentMessageId();
    QString getCurrentServiceMessageId();

    void updateMessageStatus();

private slots:
    void activateCotextMenu( QAction *pAction );
    void statusReady();
    void errorRequest();

private:
    QSharedPointer<ServiceOrderModel> _serviceOrderModel;
    QSharedPointer<ServiceModel> _serviceModel;
    QSharedPointer<QMenu> _contextMenu;
    QSharedPointer<CheckManager> _check;
    QSharedPointer<SmsManager> _sms;
    QSharedPointer<MessageModel> _messageModel;
    QSharedPointer<Db> _db;

};

#endif // SHOWSERVICEORDERVIEW_H
