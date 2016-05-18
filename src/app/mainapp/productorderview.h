#ifndef PRODUCTORDERVIEW_H
#define PRODUCTORDERVIEW_H

#include <QtWidgets>

class ProductOrderView : public QTableWidget
{
    Q_OBJECT

public:
    ProductOrderView( QWidget *parent = 0 );

private:
    void setHeaders();
};

#endif // PRODUCTORDERVIEW_H
