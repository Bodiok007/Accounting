#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "dbsetting.h"

class tst_DbSetting : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void saveSetting_dataOfSetting_returnTrue();
    void readSetting_putSettingInArrage_returnSameSetting();
};


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


void tst_DbSetting::readSetting_putSettingInArrage_returnSameSetting()
{
    DbSettingData settingData;
    settingData.databaseName = "dbName";
    settingData.hostName = "hostName";
    settingData.userName = "userName";
    settingData.password = "password";
    settingData.error = DbSettingError::NoError;

    DbSetting db;
    db.saveSetting( settingData );

    DbSettingData actual = db.readSetting();
    DbSettingData &expected = settingData;

    QCOMPARE( expected.databaseName, actual.databaseName );
    QCOMPARE( expected.hostName, actual.hostName );
    QCOMPARE( expected.userName, actual.userName );
    QCOMPARE( expected.password, actual.password );
    QCOMPARE( expected.error, actual.error );
}

QTEST_MAIN( tst_DbSetting )

#include "tst_dbsetting.moc"
