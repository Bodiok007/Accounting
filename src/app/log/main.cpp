#include "mainwindow.h"
#include "logtofile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    LogToFile logger;
    logger.log("message");

    return a.exec();
}
