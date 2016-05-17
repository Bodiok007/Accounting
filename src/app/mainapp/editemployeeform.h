#ifndef EDITUSERFORM_H
#define EDITUSERFORM_H

#include <QtWidgets>
#include "usermodel.h"
#include "changepasswordform.h"

namespace Ui {
class EditUserForm;
}

class EditEmployeeForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        EMPTY_FIELDS_ERROR,
        UPDATE_EMPLOYEE_ERROR
    };

    explicit EditEmployeeForm( QWidget *parent = 0 );
    ~EditEmployeeForm();

signals:
    void updateEmployees();

public slots:
    void setUserEditInfo( UserEditInfo &user );

private:
    void addUserInfoToForm();
    void setUserInfoFromForm();
    bool isFieldsEmpty();

    void initErrors();
    void connectSlots();

    void clearFields();
    void message( QString text );
    void logError( Errors error , QString fileName, int line );

private slots:
    void updateUser();
    void showEditPasswordForm();

private:
    Ui::EditUserForm *ui;
    QSharedPointer<ChangePasswordForm> _changePasswordForm;
    QSharedPointer<UserModel> _userModel;
    UserEditInfo _user;
    QMap<Errors, QString> _errors;
};

#endif // EDITUSERFORM_H
