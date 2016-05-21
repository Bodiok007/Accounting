#ifndef PRODUCTORDERMODEL_H
#define PRODUCTORDERMODEL_H

#include <QObject>
#include "db.h"
#include "querytype.h"

class ProductOrderModel : public QObject
{
    Q_OBJECT
public:
    explicit ProductOrderModel( QObject *parent = 0 );
    QString addOrder();
    QString getOrderId();

private:
    void initQueries();
    void logError( QString fileName, int line );

    QString lastInsertId();

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
    QString _orderId;
};

#endif // PRODUCTORDERMODEL_H
