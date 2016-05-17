#ifndef EDITUSERFORM_H
#define EDITUSERFORM_H

#include <QWidget>

namespace Ui {
class EditUserForm;
}

class EditUserForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditUserForm(QWidget *parent = 0);
    ~EditUserForm();

private:
    Ui::EditUserForm *ui;
};

#endif // EDITUSERFORM_H
