#ifndef SENDMESSAGEFORM_H
#define SENDMESSAGEFORM_H

#include <QWidget>

namespace Ui {
class SendMessageForm;
}

class SendMessageForm : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessageForm(QWidget *parent = 0);
    ~SendMessageForm();

private:
    Ui::SendMessageForm *ui;
};

#endif // SENDMESSAGEFORM_H
