#ifndef PRODUCTORDERFORM_H
#define PRODUCTORDERFORM_H

#include <QWidget>

namespace Ui {
class ProductOrderForm;
}

class ProductOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductOrderForm( QWidget *parent = 0 );
    ~ProductOrderForm();

signals:
    void closeProductOrderForm();
    void showProduct( QString orderId );

protected:
    void closeEvent( QCloseEvent *event );

private:
    Ui::ProductOrderForm *ui;
};

#endif // PRODUCTORDERFORM_H
