#ifndef LOGGER_H
#define LOGGER_H

#include "ilog.h"
#include <QSharedPointer>

class Logger
{
public:
    static QSharedPointer<Logger> getInstance();
    void log( ErrorType errorType,
              QString message,
              ErrorFileInfo errorFileInfo );

private:
    Logger( ILog *logger );

private:
    static QSharedPointer<Logger> _instance;
    QSharedPointer<ILog> _logger;
};

#endif // LOGGER_H
