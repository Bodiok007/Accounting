#include <QString>
#include <QtTest>
#include <QCoreApplication>

class tst_DbSetting : public QObject
{
    Q_OBJECT

public:
    tst_DbSetting();

private Q_SLOTS:
    void testCase1();
};

tst_DbSetting::tst_DbSetting()
{
}

void tst_DbSetting::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(tst_DbSetting)

#include "tst_dbsetting.moc"
