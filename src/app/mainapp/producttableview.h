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
    void setSoldProductModelByCategory( QString category );
    void setSoldProductModelByCost( QString lowCost, QString hightCost );
    void setSoldProductModelByCategoryAndCost( QMap<QString, QString> &data );
    void setUnsoldProductModelByBarcode( QString barcode );
    void setSoldProductModel();
    void setUnsoldProductModel();
    void setProductModel( QString orderId );
    void setProductModel( QMap<QString, QString> &filter );
    Product getSelectedProduct();

private:
    void message( QString text );

private:
    QSharedPointer<ProductModel> _productModel;
};

#endif // PRODUCTTABLEVIEW_H
