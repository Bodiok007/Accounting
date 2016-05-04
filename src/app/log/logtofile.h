#ifndef LOGGER_H
#define LOGGER_H

#include "ilog.h"
#include <QDebug>

class Logger : public ILog
{
public:
    Logger();
    virtual void log(QString message);
};

#endif // LOGGER_H
