#ifndef CUSTOMERVIEW_H
#define CUSTOMERVIEW_H

#include <QtWidgets>
#include "customermodel.h"

class CustomerTableView : public QTableView
{
    Q_OBJECT

public:
    CustomerTableView( QWidget *parent = 0 );
    QSharedPointer<CustomerModel> _customerModel;

signals:
    void editCustomer( Customer &customer );

public slots:
    void setCustomerModel();
    void setCustomerModelByPhone( QString phone );
    QString getSelectedCustomerId();
    QString getSelectedCustomerName();

protected:
    void contextMenuEvent( QContextMenuEvent *pe );

private:
    void initContextMenu();

private slots:
    void activateCotextMenu( QAction *pAction );

private:
    QSharedPointer<QMenu> _contextMenu;
};

#endif // CUSTOMERVIEW_H
