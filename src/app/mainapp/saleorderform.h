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

private:
    Ui::SaleOrderForm *ui;
    QSharedPointer<AddProductForm> _addProductForm;
    QSharedPointer<ProductModel> _productModel;
};

#endif // SALEORDERFORM_H
