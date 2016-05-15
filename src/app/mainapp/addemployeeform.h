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

private:
    void setRoles();
    void connectSlots();

    UserInfo getEmployee();
    bool isFieldsEmpty( UserInfo &user );
    QString getHashString( QCryptographicHash::Algorithm algorithm
                           , QString inputString );

    void message( QString text );
    void logError( AddEmployeeFromError error
                   , QString fileName
                   , int line );

private slots:
    void addEmployee();
    void initErrors();

private:
    Ui::AddEmployeeForm *ui;
    QSharedPointer<UserModel> _userModel;
    QMap<AddEmployeeFromError, QString> _errors;

};

#endif // ADDEMPLOYEEFORM_H
