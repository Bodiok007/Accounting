#include "addemployeeform.h"
#include "ui_addemployeeform.h"

AddEmployeeForm::AddEmployeeForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEmployeeForm)
{
    ui->setupUi(this);
}

AddEmployeeForm::~AddEmployeeForm()
{
    delete ui;
}
