#ifndef LOGTOFILE_H
#define LOGTOFILE_H

#include "ilog.h"
#include <QDebug>
#include <QDir>

class LogToFile : public ILog
{
public:
    LogToFile();
    virtual bool log(ErrorType errorType,
                     QString message,
                     ErrorFileInfo errorFileInfo);
private:
    QMap<ErrorType, QString> _errorType;

private:
    const QString LOG_DIRECTORY = QString("log");
    const QString LOG_FILE_PATH = LOG_DIRECTORY + QDir::separator() + QString("accounting.log");

private:
    void createLogFolder();
    bool writeLog(QString message);
};

#endif // LOGTOFILE_H
