#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>
#include "db.h"

class MessageModel : public QObject
{
    Q_OBJECT
public:
    explicit MessageModel( QObject *parent = 0 );

public:
    QSharedPointer<QSqlQueryModel> getModel();

private:
    QSharedPointer<QSqlQueryModel> _model;

private:
    void setHeadersToModel();
    void logError( QString fileName, int line );
};

#endif // MESSAGEMODEL_H
