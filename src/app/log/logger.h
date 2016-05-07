#ifndef LOGGER_H
#define LOGGER_H

#include "ilog.h"
#include <QSharedPointer>

class Logger
{
public:
    Logger(ILog *logger);
    void log(ErrorType errorType,
             QString message,
             ErrorFileInfo errorFileInfo);

private:
    QSharedPointer<ILog> _logger;
};

#endif // LOGGER_H
