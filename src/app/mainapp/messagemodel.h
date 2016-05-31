#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>
#include "db.h"
#include "message.h"
#include "querytype.h"

class MessageModel : public QObject
{
    Q_OBJECT

public:
    explicit MessageModel( QObject *parent = 0 );

    QSharedPointer<QSqlQueryModel> getModel();

    bool addMessage( Message &message, QString orderId );
    bool updateMessageStatus( QString messageId, QString status );

private:
    void setHeadersToModel();
    void initQueries();
    void logError( QString fileName, int line );

private:
    QSharedPointer<Db> _db;
    QSharedPointer<QSqlQueryModel> _model;
    QString _messageId;
    QMap<QueryType, QString> _queries;
};

#endif // MESSAGEMODEL_H
