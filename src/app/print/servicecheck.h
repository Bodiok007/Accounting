#ifndef SERVICECHECK_H
#define SERVICECHECK_H

#include <QObject>
#include "icheck.h"
#include "declaremetatype.h"
#include "logger.h"

class ServiceCheck : public QObject, public ICheck
{
    Q_OBJECT
public:
    explicit ServiceCheck( QObject *parent = 0 );

    bool create( QVariant &data );
    void print();

private:
    void logError( QString message, QString fileName, int line );

private:
    QList<Service> *_checkServiceList;
    QString _orderId;
    QString _employeeName;
    QString _customerName;
};

#endif // SERVICECHECK_H
