#ifndef MESSAGESETTINGFORM_H
#define MESSAGESETTINGFORM_H

#include <QtWidgets>
#include "smsmanager.h"
#include "smsclubservice.h"

namespace Ui {
class MessageSettingForm;
}

class MessageSettingForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        FIELD_EMPTY,
        SAVE_ERROR
    };

    explicit MessageSettingForm( QWidget *parent = 0 );
    ~MessageSettingForm();

    void addSettingToForm();

private slots:
    void saveSettings();

private:
    bool isFieldsEmpty();
    void initErrors();
    void message( QString text );

private:
    Ui::MessageSettingForm *ui;
    QSharedPointer<SmsManager> _sms;
    QMap<Errors, QString> _errors;
};

#endif // MESSAGESETTINGFORM_H
