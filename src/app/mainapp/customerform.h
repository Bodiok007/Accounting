#ifndef CUSTOMERFORM_H
#define CUSTOMERFORM_H

#include <QWidget>
#include "addcustomerform.h"
#include "editcustomerform.h"

namespace Ui {
class CustomerForm;
}

class CustomerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerForm( QWidget *parent = 0 );
    ~CustomerForm();

signals:
    void closeCustomerForm();

public slots:
    void setCustomerModel();
    void findCustomerByPhone();
    void editCustomer( Customer &customer );
    void showEditCustomerForm();

protected:
    void closeEvent( QCloseEvent *event );

private:
    void createEditCustomerForm();
    void connectSlots();

private:
    Ui::CustomerForm *ui;
    QSharedPointer<AddCustomerForm> _addCustomerForm;
    QSharedPointer<EditCustomerForm> _editCustomerForm;
};

#endif // CUSTOMERFORM_H
