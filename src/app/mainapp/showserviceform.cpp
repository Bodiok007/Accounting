#include "showserviceform.h"
#include "ui_showserviceform.h"

ShowServiceForm::ShowServiceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowServiceForm)
{
    ui->setupUi(this);
}

ShowServiceForm::~ShowServiceForm()
{
    delete ui;
}
