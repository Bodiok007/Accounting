#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <QString>
#include <QMap>

class ResponseParser
{
public:
    enum class Status
    {
        DELIVRD,
        ACCEPTED,
        NOT_DELIVRD
    };

    ResponseParser();
    QString getStatus( QString response );
    QString getMessageId( QString response );

private:
    void initStatuses();

private:
    QMap<Status, QString> _statuses;

};

#endif // REQUESTPARSER_H
