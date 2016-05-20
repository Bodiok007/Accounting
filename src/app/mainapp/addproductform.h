#ifndef ADDPRODUCTFORM_H
#define ADDPRODUCTFORM_H

#include <QtWidgets>
#include "productmodel.h"

namespace Ui {
class AddProductForm;
}

class AddProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddProductForm( QWidget *parent, QSharedPointer<ProductModel> productModel );
    ~AddProductForm();

signals:
    void addProduct( Product & );

private slots:
    void saveProduct();

private:
    void addCategoriesToForm();
    bool isEmpty();

    void message( QString text );
    void clearFields();

private:
    Ui::AddProductForm *ui;
    QSharedPointer<ProductModel> _productModel;
    Product _product;
};

#endif // ADDPRODUCTFORM_H
