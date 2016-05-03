#ifndef DB_H
#define DB_H

#include <QObject>

class db : public QObject
{
    Q_OBJECT
public:
    explicit db(QObject *parent = 0);

signals:

public slots:
};

#endif // DB_H