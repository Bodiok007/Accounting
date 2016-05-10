#include "logtofile.h"
#include <QDateTime>
#include <QFile>
#include <QCoreApplication>

/*!
 * \brief LogToFile::LogToFile
 */
LogToFile::LogToFile()
{
    _errorType[ ErrorType::WARNING ] = "Warning";
    _errorType[ ErrorType::ERROR ] = "Error";
}

/*!
 * \brief LogToFile::log
 * \param errorType
 * \param message
 * \param errorFileInfo
 * \return
 */
bool LogToFile::log( ErrorType errorType,
                     QString message,
                     ErrorFileInfo errorFileInfo )
{
    if ( !QFile::exists( LOG_DIRECTORY ) ) {
        createLogFolder();
    }

    QString messageToLog;
    messageToLog = "Date: "
                 + QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ) + "; "
                 + _errorType[errorType] + ": " + message + "; "
                 + "Path: " + QDir::currentPath() + "/"
                 + errorFileInfo.getFileName() + "; "
                 + "Line: " + QString::number( errorFileInfo.getLine() ) + "\n";

    bool statusOk = writeLog( messageToLog );

    return statusOk;
}


void LogToFile::createLogFolder()
{
    QDir dir;
    dir.mkdir( LOG_DIRECTORY );
}

bool LogToFile::writeLog( QString message )
{
    bool statusOk = false;
    QFile file( LOG_FILE_PATH );
    statusOk = file.open( QIODevice::ReadWrite | QIODevice::Append );

    QTextStream out( &file );
    out << message;

    file.close();

    return statusOk;
}
