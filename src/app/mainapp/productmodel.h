#ifndef PRODUCTMODEL_H
#define PRODUCTMODEL_H

#include <QObject>
#include "db.h"
#include "querytype.h"
#include "product.h"

class ProductModel : public QObject
{
    Q_OBJECT
public:
    explicit ProductModel( QObject *parent = 0 );
    QSharedPointer<QSqlQueryModel> getModel();

public slots:
    QString addProduct( Product &product );

    QMap<QString, QString> &getCategories() const;
    QStringList getCategoryList();

private:
    void initQueries();
    void logError( QString error, QString fileName, int line ) const;
    void setHeadersToModel();
    QString lastInsertId();

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
    mutable QMap<QString, QString> _categories;
    QSharedPointer<QSqlQueryModel> _model;
};

#endif // PRODUCTMODEL_H
