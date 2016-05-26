#ifndef SERVICEORDERMODEL_H
#define SERVICEORDERMODEL_H

#include <QObject>
#include "db.h"
#include "querytype.h"

class ServiceOrderModel : public QObject
{
    Q_OBJECT

public:
    explicit ServiceOrderModel( QObject *parent = 0 );
    QString addOrder( QString customerId );
    QString getOrderId();

private:
    QString lastInsertId();
    void initQueries();
    void logError( QString error, QString fileName, int line );

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
    QString _orderId;
};

#endif // SERVICEORDERMODEL_H
