#ifndef PRODUCTORDERTABLEVIEW_H
#define PRODUCTORDERTABLEVIEW_H

#include <QtWidgets>
#include "productordermodel.h"

class ProductOrderTableView : public QTableView
{
    Q_OBJECT

public:
    ProductOrderTableView( QWidget *parent = 0 );

public slots:
    void setProductOrderModel();

private:
    void message( QString text );

private:
    QSharedPointer<ProductOrderModel> _productOrderModel;
};

#endif // PRODUCTORDERTABLEVIEW_H
