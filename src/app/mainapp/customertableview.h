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

public slots:
    void setCustomerModel();
    void setCustomerModelByPhone( QString phone );
    QString getSelectedCustomerId();
};

#endif // CUSTOMERVIEW_H
