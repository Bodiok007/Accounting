#ifndef SHOWSERVICEORDERVIEW_H
#define SHOWSERVICEORDERVIEW_H

#include <QtWidgets>
#include "serviceordermodel.h"
#include "servicemodel.h"
#include "checkmanager.h"

class ShowServiceOrderView : public QTableView
{
    Q_OBJECT

public:
    ShowServiceOrderView( QWidget *parent = 0 );

    void setServiceOrderModel();

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

private slots:
    void activateCotextMenu( QAction *pAction );

private:
    QSharedPointer<ServiceOrderModel> _serviceOrderModel;
    QSharedPointer<ServiceModel> _serviceModel;
    QSharedPointer<QMenu> _contextMenu;
    QSharedPointer<CheckManager> _check;

};

#endif // SHOWSERVICEORDERVIEW_H
