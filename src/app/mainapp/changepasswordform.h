#ifndef CHANGEPASSWORDFORM_H
#define CHANGEPASSWORDFORM_H

#include <QWidget>

namespace Ui {
class ChangePasswordForm;
}

class ChangePasswordForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswordForm(QWidget *parent = 0);
    ~ChangePasswordForm();

private:
    Ui::ChangePasswordForm *ui;
};

#endif // CHANGEPASSWORDFORM_H
