#ifndef SALEORDERFORM_H
#define SALEORDERFORM_H

#include <QWidget>

namespace Ui {
class SaleOrderForm;
}

class SaleOrderForm : public QWidget
{
    Q_OBJECT

public:
    explicit SaleOrderForm( QWidget *parent = 0 );
    ~SaleOrderForm();

signals:
    void closeSaleOrderForm();

protected:
    void closeEvent( QCloseEvent *event );

private slots:
    void emitClose();

private:
    Ui::SaleOrderForm *ui;
};

#endif // SALEORDERFORM_H
