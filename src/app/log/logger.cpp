#include "logger.h"

Logger::Logger(ILog *logger)
{
    _logger = QSharedPointer<ILog>(logger);
}

void Logger::log(ErrorType errorType,
                 QString message,
                 ErrorFileInfo errorFileInfo)
{
    _logger->log(errorType, message, errorFileInfo);
}
