#ifndef PRODUCTORDERMODEL_H
#define PRODUCTORDERMODEL_H

#include <QObject>
#include "db.h"
#include "querytype.h"

class SaleModel : public QObject
{
    Q_OBJECT
public:
    explicit SaleModel( QObject *parent = 0 );
    QString addOrder();
    QString getOrderId();
    QSharedPointer<QSqlQueryModel> getModel();

private:
    void initQueries();
    void logError( QString error, QString fileName, int line );
    void setHeadersToModel();
    QString lastInsertId();

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
    QString _orderId;
    QSharedPointer<QSqlQueryModel> _model;
};

#endif // PRODUCTORDERMODEL_H
