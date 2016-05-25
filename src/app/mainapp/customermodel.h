#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include <QtWidgets>
#include "db.h"
#include "querytype.h"
#include "customer.h"

class CustomerModel : public QObject
{
    Q_OBJECT
public:
    explicit CustomerModel( QObject *parent = 0 );

signals:

public:
    QSharedPointer<QSqlQueryModel> getModel();
    QSharedPointer<QSqlQueryModel> getModelByPhone( QString phone );
    bool addCustomer( Customer &customer );

private:
    void initQueries();
    void setHeadersToModel();
    void setHeadersToModelWithList();
    void logError( QString error, QString fileName, int line );

private:
    QSharedPointer<Db> _db;
    QSharedPointer<QSqlQueryModel> _model;
    QMap<QueryType, QString> _queries;

};

#endif // CUSTOMERMODEL_H
