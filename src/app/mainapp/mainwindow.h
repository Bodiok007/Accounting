#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "saleorderform.h"
#include "productform.h"
#include "productorderform.h"

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
    void showProductForm();
    void destroyProductForm();

    void createProductOrderForm();
    void showProductOrderForm();
    void destroyProductOrderForm();

private:
    void connectSlots();

private:
    Ui::MainWindow *ui;
    QSharedPointer<SaleOrderForm> _saleOrderForm;
    QSharedPointer<ProductForm> _productForm;
    QSharedPointer<ProductOrderForm> _productOrderForm;
};

#endif // MAINWINDOW_H
