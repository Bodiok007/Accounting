#include "logger.h"
#include "logtofile.h"
#include "errorfileinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ErrorFileInfo errorFileInfo;
    errorFileInfo.setFileName( __FILE__ );
    errorFileInfo.setLine( __LINE__ );

    Logger::getInstance()->log( ErrorType::ERROR, "message from Singleton", errorFileInfo );
    //ExpLog::getInstance();//->log( ErrorType::ERROR, "message from exp", errorFileInfo );
    return a.exec();
}
