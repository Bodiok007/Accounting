#ifndef CHECKMANAGER_H
#define CHECKMANAGER_H

#include <QObject>
#include <QtWidgets>
#include "icheck.h"

class CheckManager : public QObject
{
    Q_OBJECT
public:
    explicit CheckManager( QObject *parent, ICheck *check );

public slots:
    void print();
    bool create( QVariant &data );

private:
    QSharedPointer<ICheck> _check;
};

#endif // CHECKMANAGER_H
