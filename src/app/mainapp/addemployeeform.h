#ifndef ADDEMPLOYEEFORM_H
#define ADDEMPLOYEEFORM_H

#include <QWidget>
#include "usermodel.h"
#include "addemployeeerror.h"
#include "querytype.h"

namespace Ui {
class AddEmployeeForm;
}

class AddEmployeeForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddEmployeeForm(QWidget *parent = 0);
    ~AddEmployeeForm();

signals:
    void updateEmployees();

private:
    void setRoles();
    void initErrors();
    void connectSlots();

    UserInfo getEmployee();
    bool isFieldsEmpty( UserInfo &user );
    QString getHashString( QCryptographicHash::Algorithm algorithm
                           , QString inputString );

    void clearPasswordFields();
    void clearFields();
    void message( QString text );
    void logError( AddEmployeeFromError error
                   , QString fileName
                   , int line );

private slots:
    void addEmployee();

private:
    Ui::AddEmployeeForm *ui;
    QSharedPointer<UserModel> _userModel;
    QMap<AddEmployeeFromError, QString> _errors;

};

#endif // ADDEMPLOYEEFORM_H
