#include "changepasswordform.h"
#include "ui_changepasswordform.h"

ChangePasswordForm::ChangePasswordForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswordForm)
{
    ui->setupUi(this);
}

ChangePasswordForm::~ChangePasswordForm()
{
    delete ui;
}
