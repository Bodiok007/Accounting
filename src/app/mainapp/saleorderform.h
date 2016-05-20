#ifndef SALEORDERFORM_H
#define SALEORDERFORM_H

#include <QWidget>
#include "addproductform.h"

namespace Ui {
class SaleOrderForm;
}

class SaleOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit SaleOrderForm( QWidget *parent = 0 );
    ~SaleOrderForm();

signals:
    void closeSaleOrderForm();

protected:
    void closeEvent( QCloseEvent *event );

private slots:
    void emitClose();
    void addProduct( Product &product );
    void addOrder();

private:
    void addProductToForm();
    void message( QString text );

private:
    Ui::SaleOrderForm *ui;
    QSharedPointer<AddProductForm> _addProductForm;
    QSharedPointer<ProductModel> _productModel;
    QList<Product> _productList;
};

#endif // SALEORDERFORM_H
