#ifndef CUSTOMERFORM_H
#define CUSTOMERFORM_H

#include <QWidget>
#include "addcustomerform.h"

namespace Ui {
class CustomerForm;
}

class CustomerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerForm( QWidget *parent = 0 );
    ~CustomerForm();

public slots:
    void setCustomerModel();

private:
    Ui::CustomerForm *ui;
    QSharedPointer<AddCustomerForm> _addCustomerForm;
};

#endif // CUSTOMERFORM_H
