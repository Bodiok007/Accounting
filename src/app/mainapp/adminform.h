#ifndef ADMINFORM_H
#define ADMINFORM_H

#include <QWidget>
#include "messagemodel.h"
#include "editemployeeform.h"
#include "addemployeeform.h"
#include "messagesettingform.h"
#include "addproductform.h"
#include "editproductform.h"

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
    void createAddProductForm();
    void createEditProductForm();
    void createProductModel();
    void message( QString text );

private slots:
    void showEditEmployeeForm();
    void showEditProductForm();
    void showAddEmployeeForm();
    void showAddProductForm();
    void showMessageSettingForm();
    void setEmployeeModel();
    void setMessageModel();
    void setProductModel();
    void editEmployee( UserEditInfo user );
    void addEmployee();
    void addProductToDb( Product &product );
    void emitClose();

private:
    Ui::AdminForm *ui;
    QSharedPointer<EditEmployeeForm> _editEmployeeForm;
    QSharedPointer<EditProductForm> _editProductForm;
    QSharedPointer<AddEmployeeForm> _addEmployeeForm;
    QSharedPointer<MessageSettingForm> _messageSettingForm;
    QSharedPointer<AddProductForm> _addProductForm;
    QSharedPointer<ProductModel> _productModel;
};

#endif // ADMINFORM_H
