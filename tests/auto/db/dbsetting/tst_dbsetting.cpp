#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "dbsetting.h"

class tst_DbSetting : public QObject
{
    Q_OBJECT

public:
    tst_DbSetting();

private Q_SLOTS:
    void saveSetting_dataOfSetting_returnTrue();
    //void readSetting_putSettingInArrage_returnSameSetting();
};


tst_DbSetting::tst_DbSetting()
{
}


void tst_DbSetting::saveSetting_dataOfSetting_returnTrue()
{
    DbSettingData settingData;
    settingData.databaseName = "dbName";
    settingData.hostName = "hostName";
    settingData.userName = "userName";
    settingData.password = "password";

    DbSetting db;
    bool actual = db.saveSetting( settingData );
    bool expected = true;

    QCOMPARE( expected, actual );
}


/*void tst_DbSetting::readSetting_putSettingInArrage_returnSameSetting()
{
    DbSettingData settingData;
    settingData.databaseName = "dbName";
    settingData.hostName = "hostName";
    settingData.userName = "userName";
    settingData.password = "password";

    DbSetting db;
    db.saveSetting( settingData );

    DbSettingData actual = db.readSetting();
    DbSettingData &expected = settingData;

    QCOMPARE(expected.databaseName, actual.databaseName);
}*/

QTEST_MAIN(tst_DbSetting)

#include "tst_dbsetting.moc"
