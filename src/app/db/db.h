#ifndef DB_H
#define DB_H

#include <QObject>

class Db : public QObject
{
    Q_OBJECT
public:
    explicit Db(QObject *parent = 0);

signals:

public slots:
};

#endif // DB_H
