#ifndef EMPLOYEETABLEVIEW_H
#define EMPLOYEETABLEVIEW_H

#include <QtWidgets>
#include "usermodel.h"

class EmployeeTableView : public QTableView
{
    Q_OBJECT

public:
    EmployeeTableView( QWidget *parent );

    enum class Errors
    {
        NO_ADD_ROLE_ERROR,
        NO_REMOVE_ROLE_ERROR,
        ADD_ROLE_ERROR,
        REMOVE_ROLE_ERROR
    };

public slots:
    void setEmployeeModel();

signals:
    void editUser( UserEditInfo user );

protected:
    virtual void contextMenuEvent( QContextMenuEvent *pe );

private:
    void initContextMenu();
    void initError();

    QString getCurrentEmployeeId();
    void addAdminRoleToUser();
    void removeAdminRoleFromUser();
    UserEditInfo getCurrentUserInfo();

    void message( QString text );
    void logError( Errors error
                   , QString fileName
                   , int line );

private slots:
    void activateCotextMenu( QAction *pAction );

private:
    QSharedPointer<UserModel> _model;
    QSharedPointer<QMenu> _contextMenu;
    QMap<Errors, QString> _errors;

};

#endif // EMPLOYEETABLEVIEW_H
