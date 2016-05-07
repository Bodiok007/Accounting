#include "errorfileinfo.h"
#include <QStringList>

/*!
 * \brief ErrorFileInfo::setName
 * \param fileName
 */
void ErrorFileInfo::setFileName(QString fileName)
{
    QStringList arrayFilePath = fileName.split("\\");
    _fileName = arrayFilePath[ arrayFilePath.length() - 1 ];
}

/*!
 * \brief ErrorFileInfo::setLine
 * \param line
 */
void ErrorFileInfo::setLine(int line)
{
    _line = line;
}

/*!
 * \brief ErrorFileInfo::getFileName
 * \return
 */
QString ErrorFileInfo::getFileName()
{
    return _fileName;
}

/*!
 * \brief ErrorFileInfo::getLine
 * \return
 */
int ErrorFileInfo::getLine()
{
    return _line;
}
