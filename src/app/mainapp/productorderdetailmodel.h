#ifndef PRODUCTORDERDETAILMODEL_H
#define PRODUCTORDERDETAILMODEL_H

#include <QObject>
#include "db.h"
#include "querytype.h"
#include "product.h"

class ProductOrderDetailModel : public QObject
{
    Q_OBJECT
public:
    explicit ProductOrderDetailModel( QObject *parent = 0 );

    bool addOrderDetail( QString orderId, Product &product );

private:
    void initQueries();
    void logError( QString fileName, int line );

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
};

#endif // PRODUCTORDERDETAILMODEL_H
