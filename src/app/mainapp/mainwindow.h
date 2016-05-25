#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "saleorderform.h"
#include "productform.h"
#include "saleform.h"
#include "customerform.h"
#include "serviceorderform.h"

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

    void createServiceOrderForm();
    void showServiceOrderForm();
    void destroyServiceOrderForm();

private:
    void connectSlots();

private:
    Ui::MainWindow *ui;
    QSharedPointer<SaleOrderForm> _saleOrderForm;
    QSharedPointer<ProductForm> _productForm;
    QSharedPointer<SaleForm> _productOrderForm;
    QSharedPointer<CustomerForm> _customerForm;
    QSharedPointer<ServiceOrderForm> _serviceOrderForm;
};

#endif // MAINWINDOW_H
