#ifndef PRODUCTORDERTABLEVIEW_H
#define PRODUCTORDERTABLEVIEW_H

#include <QtWidgets>
#include "productmodel.h"
#include "checkmanager.h"
#include "productordermodel.h"

class ProductOrderTableView : public QTableView
{
    Q_OBJECT

public:
    ProductOrderTableView( QWidget *parent = 0 );

public slots:
    void setProductOrderModel();

signals:
    void showProduct( QString orderId );

protected:
    void contextMenuEvent( QContextMenuEvent *pe );

private:
    void printCheck();
    void print( QStringList &general
                , QList<Product> &productList );

    QString getCurrentOrderId();
    void initContextMenu();
    void message( QString text );

private slots:
    void activateCotextMenu( QAction *pAction );

private:
    QSharedPointer<ProductModel> _productModel;
    QSharedPointer<ProductOrderModel> _productOrderModel;
    QSharedPointer<CheckManager> _check;
    QSharedPointer<QMenu> _contextMenu;
};

#endif // PRODUCTORDERTABLEVIEW_H
