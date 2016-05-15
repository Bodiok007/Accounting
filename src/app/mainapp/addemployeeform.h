#ifndef ADDEMPLOYEEFORM_H
#define ADDEMPLOYEEFORM_H

#include <QWidget>

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
    Ui::AddEmployeeForm *ui;
};

#endif // ADDEMPLOYEEFORM_H
