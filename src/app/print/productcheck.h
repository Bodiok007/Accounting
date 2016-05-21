#ifndef PRODUCTCHECK_H
#define PRODUCTCHECK_H

#include <QObject>
#include "icheck.h"
#include "declaremetatype.h"
#include "logger.h"

class ProductCheck : public QObject, public ICheck
{
    Q_OBJECT
public:
    explicit ProductCheck( QObject *parent = 0 );

    bool create( QVariant &data );
    void print();

signals:

public slots:

private:
    void logError( QString message, QString fileName, int line );

private:
    QList<Product> *_checkProductList;
    QString _orderId;
    QString _employeeName;
};

#endif // PRODUCTCHECK_H
