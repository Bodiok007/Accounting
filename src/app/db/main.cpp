#include "dbsetting.h"
#include "mysqldb.h"
#include "db.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //DbSetting dbSetting;
    auto db = Db::getInstance();
    bool connectionOk = db->connectToDb();
    qDebug() << "connection " << connectionOk;

    /*DbSettingData dt;
    dt.databaseName = "accounting";
    dt.hostName = "localhost";
    dt.password = "";
    dt.userName = "root";

    set.saveSetting(dt);*/

    QStringList arg; arg << "1111";
    bool statusOk = db->query( QString( "select * from employe where password = ?" ), arg );

    if ( statusOk ) {
        auto data = db->getData();
        data->next();
        qDebug() << data->value(0).toString();
    }

    /*IDb * fb = new MySqlDb();
    fb->connectToDb();
    delete fb;*/

    return a.exec();
}
