#ifndef SERVICEORDERFORM_H
#define SERVICEORDERFORM_H

#include <QWidget>
#include "customermodel.h"
#include "addcustomerform.h"
#include "addserviceform.h"
#include "db.h"
#include "servicemodel.h"
#include "serviceordermodel.h"
#include "serviceorderdetailmodel.h"
#include "checkmanager.h"

namespace Ui {
class ServiceOrderForm;
}

class ServiceOrderForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        SERVICE_LIST_EMPTY,
        NOT_CHOOSE_CUSTOMER,
        ADD_ORDER_ERROR
    };

    explicit ServiceOrderForm( QWidget *parent = 0 );
    ~ServiceOrderForm();

signals:
    void closeServiceOrderForm();

protected:
    void closeEvent( QCloseEvent *event );

private:
    void connectSlots();
    void initFields();
    void initErrors();
    void addServiceToForm();
    void message( QString text );
    bool isPrintCheck();

private slots:
    void findCustomerByPhone();
    void addService( Service &service );
    void addOrder();
    void printCheck();

private:
    Ui::ServiceOrderForm *ui;
    QSharedPointer<Db> _db;
    QSharedPointer<CustomerModel> _customerModel;
    QSharedPointer<ServiceModel> _serviceModel;
    QSharedPointer<ServiceOrderModel> _serviceOrderModel;
    QSharedPointer<ServiceOrderDetailModel> _serviceOrderDetailModel;
    QSharedPointer<AddCustomerForm> _addCustomerForm;
    QSharedPointer<AddServiceForm> _addServiceForm;
    QList<Service> _serviceList;
    QMap<Errors, QString> _errors;

    QSharedPointer<CheckManager> _check;
};

#endif // SERVICEORDERFORM_H
