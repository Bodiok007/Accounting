#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include "db.h"
#include "userinfo.h"
#include "querytype.h"

class UserModel : public QObject
{
    Q_OBJECT

public:
    explicit UserModel( QObject *parent = 0 );

public:
    QMap<QString, QString> &getRoles();
    QStringList getListRoles();
    QSharedPointer<QSqlQueryModel> getModel();

    bool addUser( UserInfo user );
    bool addRoleToUser( QString userId, QString role );
    bool removeRoleFromUser( QString userId, QString role );

private:
    void logError( QString fileName, int line );
    void setRoles();
    void initQueries();
    void setHeadersToModel();

private:
    QSharedPointer<Db> _db;
    QMap<QString, QString> _roles;
    QMap<QueryType, QString> _queries;
    QSharedPointer<QSqlQueryModel> _model;
};

#endif // USERMODEL_H
