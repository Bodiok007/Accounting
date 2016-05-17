#include "edituserform.h"
#include "ui_edituserform.h"

EditUserForm::EditUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditUserForm)
{
    ui->setupUi(this);
}

EditUserForm::~EditUserForm()
{
    delete ui;
}
