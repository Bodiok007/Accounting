#ifndef LOGTOFILE_H
#define LOGTOFILE_H

#include "ilog.h"
#include <QDebug>

class LogToFile : public ILog
{
public:
    LogToFile();
    virtual void log(QString message);
};

#endif // LOGTOFILE_H
