#include "adminform.h"
#include "ui_adminform.h"

AdminForm::AdminForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminForm)
{
    ui->setupUi(this);
    ui->tableMessage->setMessageModel();
}

AdminForm::~AdminForm()
{
    delete ui;
}
