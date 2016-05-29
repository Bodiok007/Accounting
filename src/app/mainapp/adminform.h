#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include "messagemodel.h"
#include "editemployeeform.h"
#include "addemployeeform.h"
#include "messagesettingform.h"

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
    void closeEvent( QCloseEvent *event );

private:
    void connectSlots();
    void createEditEmployeeForm();
    void createAddEmployeeForm();
    void createMessageSettingForm();

private slots:
    void showEditEmployeeForm();
    void showAddEmployeeForm();
    void showMessageSettingForm();
    void setEmployeeModel();
    void setMessageModel();
    void editEmployee( UserEditInfo user );
    void addEmployee();
    void emitClose();

private:
    Ui::AdminForm *ui;
    QSharedPointer<EditEmployeeForm> _editEmployeeForm;
    QSharedPointer<AddEmployeeForm> _addEmployeeForm;
    QSharedPointer<MessageSettingForm> _messageSettingForm;
};

#endif // ADMINFORM_H
