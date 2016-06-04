#ifndef ADDEXISTPRODUCTFORM_H
#define ADDEXISTPRODUCTFORM_H

#include <QtWidgets>
#include "product.h"

namespace Ui {
class AddExistProductForm;
}

class AddExistProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddExistProductForm( QWidget *parent = 0 );
    ~AddExistProductForm();

signals:
    void addProduct( Product &product );

private slots:
    void addSelectedProduct();
    void searchProduct();

private:
    void message( QString text );

private:
    Ui::AddExistProductForm *ui;
    Product _product;
};

#endif // ADDEXISTPRODUCTFORM_H
