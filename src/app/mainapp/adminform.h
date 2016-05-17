#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include "messagemodel.h"
#include "editemployeeform.h"
#include "addemployeeform.h"

namespace Ui {
class AdminForm;
}

class AdminForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminForm( QWidget *parent = 0 );
    ~AdminForm();

signals:
    void closeAdminForm();

protected:
    virtual void closeEvent( QCloseEvent *event );

private:
    void connectSlots();
    void createEditEmployeeForm();
    void createAddEmployeeForm();

private slots:
    void showEditEmployeeForm();
    void showAddEmployeeForm();
    void setEmployeeModel();
    void setMessageModel();
    void editEmployee( UserEditInfo user );
    void addEmployee();
    void emitClose();

private:
    Ui::AdminForm *ui;
    QSharedPointer<EditEmployeeForm> _editEmployeeForm;
    QSharedPointer<AddEmployeeForm> _addEmployeeForm;

};

#endif // ADMINFORM_H
