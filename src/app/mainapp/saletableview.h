#ifndef PRODUCTORDERTABLEVIEW_H
#define PRODUCTORDERTABLEVIEW_H

#include <QtWidgets>
#include "productmodel.h"
#include "checkmanager.h"
#include "salemodel.h"

class SaleTableView : public QTableView
{
    Q_OBJECT

public:
    SaleTableView( QWidget *parent = 0 );

public slots:
    void setSaleModel();

signals:
    void showSale( QString orderId );

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
    QSharedPointer<SaleModel> _productOrderModel;
    QSharedPointer<CheckManager> _check;
    QSharedPointer<QMenu> _contextMenu;
};

#endif // PRODUCTORDERTABLEVIEW_H
