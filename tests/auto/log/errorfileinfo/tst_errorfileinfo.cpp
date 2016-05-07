#include <QString>
#include <QtTest>
#include "errorfileinfo.h"

class tst_ErrorFileInfo : public QObject
{
    Q_OBJECT

public:
    tst_ErrorFileInfo();

private Q_SLOTS:
    void getFileName_setFileNameWithPath_returnsName();
    void getFileName_setOnlyFileName_returnsName();
    void getLine_setValidLine_returnsLine();
};

tst_ErrorFileInfo::tst_ErrorFileInfo()
{
}

void tst_ErrorFileInfo::getFileName_setFileNameWithPath_returnsName()
{
    QString testData = QString("src\\app\\somefile.cpp");

    ErrorFileInfo errorFileInfo;
    errorFileInfo.setFileName(testData);

    QString actual = errorFileInfo.getFileName();
    QString expected = QString("somefile.cpp");

    QCOMPARE(expected, actual);
}

void tst_ErrorFileInfo::getFileName_setOnlyFileName_returnsName()
{
    QString testData = QString("somefile.cpp");

    ErrorFileInfo errorFileInfo;
    errorFileInfo.setFileName(testData);

    QString actual = errorFileInfo.getFileName();
    QString expected = testData;

    QCOMPARE(expected, actual);
}

void tst_ErrorFileInfo::getLine_setValidLine_returnsLine()
{
    int testData = 5;

    ErrorFileInfo errorFileInfo;
    errorFileInfo.setLine(testData);

    int actual = errorFileInfo.getLine();
    int expected = testData;

    QCOMPARE(expected, actual);
}

QTEST_APPLESS_MAIN(tst_ErrorFileInfo)

#include "tst_errorfileinfo.moc"
