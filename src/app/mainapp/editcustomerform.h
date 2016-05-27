#ifndef EDITCUSTOMERFORM_H
#define EDITCUSTOMERFORM_H

#include <QWidget>
#include "customer.h"
#include "customermodel.h"

namespace Ui {
class EditCustomerForm;
}

class EditCustomerForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        EMPTY_FIELDS_ERROR,
        UPDATE_CUSTOMER_ERROR
    };

    explicit EditCustomerForm( QWidget *parent = 0 );
    ~EditCustomerForm();

    void setCustomer( Customer customer );


signals:
    void updateCustomers();

private:
    bool isFieldsEmpty();
    void clearFields();
    void addCustomerToForm();

    void initErrors();
    void message( QString text );
    void logError( Errors error
                   , QString fileName
                   , int line );

private slots:
    void updateCustomer();

private:
    Ui::EditCustomerForm *ui;
    QSharedPointer<CustomerModel> _customerModel;
    QMap<Errors, QString> _errors;
    Customer _customer;
};

#endif // EDITCUSTOMERFORM_H
