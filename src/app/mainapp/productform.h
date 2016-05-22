#ifndef PRODUCTFORM_H
#define PRODUCTFORM_H

#include <QWidget>

namespace Ui {
class ProductForm;
}

class ProductForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductForm( QWidget *parent = 0 );
    ~ProductForm();

private:
    Ui::ProductForm *ui;
};

#endif // PRODUCTFORM_H
