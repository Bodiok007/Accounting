#ifndef SERVICEMODEL_H
#define SERVICEMODEL_H

#include <QWidget>
#include "db.h"
#include "querytype.h"
#include "customermodel.h"
#include "service.h"

class ServiceModel : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceModel( QWidget *parent = 0 );

    QSharedPointer<QSqlQueryModel> getModel();
    QSharedPointer<QSqlQueryModel> getModel( QString orderId );

public slots:
    QMap<QString, QString> &getCategories() const;
    QStringList getCategoryList();
    QString addService( Service &service );


private:
    void initQueries();
    void logError( QString error, QString fileName, int line ) const;
    QString lastInsertId();
    void setHeadersToModel();

private:
    QSharedPointer<Db> _db;
    mutable QMap<QString, QString> _categories;
    QMap<QueryType, QString> _queries;
    QSharedPointer<QSqlQueryModel> _model;
};

#endif // SERVICEMODEL_H
