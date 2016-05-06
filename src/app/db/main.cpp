#include "dbsetting.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbSetting dbSetting;

    return a.exec();
}
