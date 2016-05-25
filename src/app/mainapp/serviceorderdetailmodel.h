#ifndef SERVICEORDERDETAILMODEL_H
#define SERVICEORDERDETAILMODEL_H

#include <QObject>
#include "querytype.h"
#include "db.h"

class ServiceOrderDetailModel : public QObject
{
    Q_OBJECT
public:
    explicit ServiceOrderDetailModel( QObject *parent = 0 );

    bool addOrderDetail( QString orderId, QString serviceId );

private:
    void initQueries();
    void logError( QString fileName, int line );

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
};

#endif // SERVICEORDERDETAILMODEL_H
