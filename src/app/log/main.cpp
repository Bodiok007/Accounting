#include "logger.h"
#include "logtofile.h"
#include "errorfileinfo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ErrorFileInfo errorFileInfo;
    errorFileInfo.setFileName(__FILE__);
    errorFileInfo.setLine(__LINE__);

    Logger logger(new LogToFile());
    logger.log(ErrorType::ERROR, "message", errorFileInfo);

    return a.exec();
}
