#ifndef ILOG_H
#define ILOG_H

#include <QString>
#include "errorlevel.h"
#include "errorfileinfo.h"

class ILog
{
public:
    virtual bool log( ErrorType errorType,
                      QString message,
                      ErrorFileInfo errorFileInfo ) = 0;
};

#endif // ILOG_H
