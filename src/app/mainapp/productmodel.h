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

signals:

public slots:
    bool saveProduct( Product *product );

private:
    void initQueries();
    void logError( QString fileName, int line );

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
};

#endif // PRODUCTMODEL_H
