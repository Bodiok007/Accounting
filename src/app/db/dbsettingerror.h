#ifndef DBSETTINGERROR_H
#define DBSETTINGERROR_H

enum class DbSettingError
{
    NoError,
    FileNotExists,
    FolderNotExists,
    ErrorOpenFileForReading,
    ErrorOpenFileForWriting
};

#endif // DBSETTINGERROR_H
