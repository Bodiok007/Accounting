#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H

#include <QtWidgets>
#include "productmodel.h"

namespace Ui {
class ProductForm;
}

class ProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductForm( QWidget *parent = 0 );
    ~ProductForm();

    void setProductModel();
    void setProductModel( QString orderId );
    void setSoldProductModel();
    void setSoldProductModelByCategory( QString category );
    void setSoldProductModelByCost();
    void setSoldProductModelByCategoryAndCost( QString category );

signals:
    void closeProductForm();

public slots:
    void search();

protected:
    void closeEvent( QCloseEvent *event );

private:
    void setCategories();

private:
    Ui::ProductForm *ui;
    QSharedPointer<ProductModel> _productModel;
};

#endif // PRODUCTFORM_H
