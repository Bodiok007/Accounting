#ifndef EDITPRODUCTFORM_H
#define EDITPRODUCTFORM_H

#include <QtWidgets>
#include "productmodel.h"

namespace Ui {
class EditProductForm;
}

class EditProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditProductForm( QWidget *parent
                              , QSharedPointer<ProductModel> model );
    ~EditProductForm();

    void addProductToForm( Product &product );

signals:
    void updateProducts();

private:
    void addCategoriesToForm();
    bool isFieldEmpty();
    void setProductInfoFromForm();
    void message( QString text );
    void clearFields();

private slots:
    void saveEditedProduct();

private:
    Ui::EditProductForm *ui;
    QSharedPointer<ProductModel> _productModel;
    Product _product;
};

#endif // EDITPRODUCTFORM_H
