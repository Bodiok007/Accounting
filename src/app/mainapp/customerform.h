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

signals:
    void closeCustomerForm();

public slots:
    void setCustomerModel();
    void findCustomerByPhone();

protected:
    void closeEvent( QCloseEvent *event );

private:
    Ui::CustomerForm *ui;
    QSharedPointer<AddCustomerForm> _addCustomerForm;
};

#endif // CUSTOMERFORM_H
