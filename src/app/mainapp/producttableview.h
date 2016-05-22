#ifndef PRODUCTTABLEVIEW_H
#define PRODUCTTABLEVIEW_H

#include <QObject>
#include <QtWidgets>
#include "productmodel.h"

class ProductTableView : public QTableView
{
    Q_OBJECT

public:
    ProductTableView( QWidget *parent = 0 );

public slots:
    void setProductModel();

private:
    void message( QString text );

private:
    QSharedPointer<ProductModel> _productModel;
};

#endif // PRODUCTTABLEVIEW_H