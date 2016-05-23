#ifndef PRODUCTORDERFORM_H
#define PRODUCTORDERFORM_H

#include <QWidget>

namespace Ui {
class ProductOrderForm;
}

class SaleForm : public QWidget
{
    Q_OBJECT

public:
    explicit SaleForm( QWidget *parent = 0 );
    ~SaleForm();

signals:
    void closeProductOrderForm();
    void showSale( QString orderId );

protected:
    void closeEvent( QCloseEvent *event );

private:
    Ui::ProductOrderForm *ui;
};

#endif // PRODUCTORDERFORM_H
