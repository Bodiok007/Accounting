#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "logtofile.h"

class tst_Logtofile : public QObject
{
    Q_OBJECT

public:
    tst_Logtofile();

private Q_SLOTS:
    void log_setParameter_returnTrue();
};

tst_Logtofile::tst_Logtofile()
{
}

void tst_Logtofile::log_setParameter_returnTrue()
{
    ErrorFileInfo errorFileInfo;
    errorFileInfo.setFileName(__FILE__);
    errorFileInfo.setLine(__LINE__);

    LogToFile logToFile;
    bool statusOk = logToFile.log(ErrorType::WARNING, "warnign message", errorFileInfo);

    QCOMPARE(true, statusOk);
}

QTEST_MAIN(tst_Logtofile)

#include "tst_logtofile.moc"
