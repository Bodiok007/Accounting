#include "sendmessageform.h"
#include "ui_sendmessageform.h"

SendMessageForm::SendMessageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessageForm)
{
    ui->setupUi(this);
}

SendMessageForm::~SendMessageForm()
{
    delete ui;
}
