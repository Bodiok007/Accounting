#ifndef LOGGER_H
#define LOGGER_H

#include "ilog.h"
#include <QSharedPointer>

class Logger
{
public:
    Logger();

private:
    QSharedPointer<ILog> _logger;
};

#endif // LOGGER_H
