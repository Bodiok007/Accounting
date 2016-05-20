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
    bool addProduct( Product &product );

    QMap<QString, QString> &getCategories() const;
    QStringList getCategoryList();

private:
    void initQueries();
    void logError( QString fileName, int line ) const;

private:
    QSharedPointer<Db> _db;
    QMap<QueryType, QString> _queries;
    mutable QMap<QString, QString> _categories;
};

#endif // PRODUCTMODEL_H