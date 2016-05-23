#ifndef ADDCUSTOMERFORM_H
#define ADDCUSTOMERFORM_H

#include <QWidget>
#include "customermodel.h"

namespace Ui {
class AddCustomerForm;
}

class AddCustomerForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        EMPTY_FIELDS_ERROR,
        ADD_CUSTOMER_ERROR
    };

    explicit AddCustomerForm( QWidget *parent = 0 );
    ~AddCustomerForm();

signals:
    void updateCustomers();

private slots:
    void addCustomer();

private:
    bool isFieldsEmpty( Customer &customer );
    void clearFields();

    void initErrors();
    void message( QString text );
    void logError( Errors error
                   , QString fileName
                   , int line );

private:
    Ui::AddCustomerForm *ui;
    QSharedPointer<CustomerModel> _customerModel;
    QMap<Errors, QString> _errors;
};

#endif // ADDCUSTOMERFORM_H
