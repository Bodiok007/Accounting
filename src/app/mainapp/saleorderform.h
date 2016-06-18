#ifndef SALEORDERFORM_H
#define SALEORDERFORM_H

#include <QWidget>
#include "addproductform.h"
#include "salemodel.h"
#include "productorderdetailmodel.h"
#include "checkmanager.h"
#include "addexistproductform.h"

namespace Ui {
class SaleOrderForm;
}

class SaleOrderForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        PRODUCT_LIST_EMPTY_FOR_SAVE,
        PRODUCT_LIST_EMPTY_FOR_PRINT,
        ADD_ORDER_ERROR
    };

    explicit SaleOrderForm( QWidget *parent = 0 );
    ~SaleOrderForm();

signals:
    void closeSaleOrderForm();

protected:
    void closeEvent( QCloseEvent *event );

private:
    void addProductToForm();
    void initFields();
    void initErrors();
    void connectSlots();
    void message( QString text );
    bool isPrintCheck();

private slots:
    void emitClose();
    void addProduct( Product &product );
    void addOrder();
    void printCheck();

private:
    Ui::SaleOrderForm *ui;
    QSharedPointer<Db> _db;

    /*QSharedPointer<AddProductForm> _addProductForm;*/
    QSharedPointer<AddExistProductForm> _addExistProductForm;

    QSharedPointer<ProductModel> _productModel;
    QSharedPointer<SaleModel> _saleModel;
    QSharedPointer<ProductOrderDetailModel> _productOrderDetailModel;

    QSharedPointer<CheckManager> _check;

    QList<Product> _productList;
    QMap<Errors, QString> _errors;
};

#endif // SALEORDERFORM_H
