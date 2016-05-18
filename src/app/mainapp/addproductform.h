#ifndef ADDPRODUCTFORM_H
#define ADDPRODUCTFORM_H

#include <QWidget>

namespace Ui {
class AddProductForm;
}

class AddProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddProductForm( QWidget *parent = 0 );
    ~AddProductForm();

private:
    Ui::AddProductForm *ui;
};

#endif // ADDPRODUCTFORM_H
