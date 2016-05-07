#ifndef ERRORFILEINFO_H
#define ERRORFILEINFO_H

#include <QString>

class ErrorFileInfo
{
public:
    void setFileName(QString fileName);
    void setLine(int line);
    QString getFileName();
    int getLine();

private:
    QString _fileName;
    int _line;
};

#endif // ERRORFILEINFO_H
