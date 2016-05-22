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

    void setProductModel();
    void setProductModel( QString orderId );

signals:
    void closeProductForm();

protected:
    void closeEvent( QCloseEvent *event );

private:
    Ui::ProductForm *ui;
};

#endif // PRODUCTFORM_H
