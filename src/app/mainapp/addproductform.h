#ifndef ADDPRODUCTFORM_H
#define ADDPRODUCTFORM_H

#include <QWidget>
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

private:
    void setCategories();

private:
    Ui::AddProductForm *ui;
    QSharedPointer<ProductModel> _productModel;
};

#endif // ADDPRODUCTFORM_H
