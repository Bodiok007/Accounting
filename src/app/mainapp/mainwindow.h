#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "saleorderform.h"
#include "productform.h"
#include "saleform.h"
#include "customerform.h"
#include "serviceorderform.h"
#include "showserviceorderform.h"
#include "showserviceform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = 0 );
    ~MainWindow();

signals:
    void closeMainForm();

protected:
    void closeEvent( QCloseEvent *event );

private slots:
    void emitClose();

    void createSaleOrderForm();
    void showSaleOrderForm();
    void destroySaleOrderForm();

    void createProductForm();
    void showSaleForm();
    void createProductForm( QString orderId );
    void showSaleForm( QString orderId );
    void destroyProductForm();

    void createProductOrderForm();
    void showProductOrderForm();
    void destroyProductOrderForm();

    void createCustomerForm();
    void showCustomerForm();
    void destroyCustomerForm();

    void createAddServiceOrderForm();
    void showAddServiceOrderForm();
    void destroyAddServiceOrderForm();

    void createShowServiceOrderForm();
    void showShowServiceOrderForm();
    void destroyShowServiceOrderForm();

    void createShowServiceForm();
    void showShowServiceForm();
    void createShowServiceForm( QString orderId );
    void showShowServiceForm( QString orderId );
    void destroyShowServiceForm();

private:
    void connectSlots();

private:
    Ui::MainWindow *ui;
    QSharedPointer<SaleOrderForm> _saleOrderForm;
    QSharedPointer<ProductForm> _productForm;
    QSharedPointer<SaleForm> _productOrderForm;
    QSharedPointer<CustomerForm> _customerForm;
    QSharedPointer<ServiceOrderForm> _serviceOrderForm;
    QSharedPointer<ShowServiceOrderForm> _showServiceOrderForm;
    QSharedPointer<ShowServiceForm> _showServiceForm;
};

#endif // MAINWINDOW_H
