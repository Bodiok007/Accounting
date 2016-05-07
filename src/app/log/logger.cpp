#include "logger.h"
#include "logtofile.h"


Logger::Logger( ILog *logger )
{
    _logger = QSharedPointer<ILog>( logger );
}


QSharedPointer<Logger> Logger::getInstance()
{
    if ( _instance.isNull() ) {
        _instance = QSharedPointer<Logger>(
                    new Logger( new LogToFile() ) );
    }

    return _instance;
}


void Logger::log( ErrorType errorType,
                  QString message,
                  ErrorFileInfo errorFileInfo )
{
    _logger->log( errorType, message, errorFileInfo );
}


QSharedPointer<Logger> Logger::_instance;
