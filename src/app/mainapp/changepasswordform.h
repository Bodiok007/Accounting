#ifndef CHANGEPASSWORDFORM_H
#define CHANGEPASSWORDFORM_H

#include <QtWidgets>
#include "usermodel.h"

namespace Ui {
class ChangePasswordForm;
}

class ChangePasswordForm : public QWidget
{
    Q_OBJECT

public:
    enum class Errors
    {
        NO_ERRORR,
        EMPTY_FIELDS_ERROR,
        PASSWORDS_NOT_EQUALS,
        UPDATE_PASSWORD_ERROR
    };

    explicit ChangePasswordForm( QWidget *parent
                                 , QSharedPointer<UserModel> model );
    ~ChangePasswordForm();

    void setUserId( QString userId );

private:
    void initErrors();
    void clearFields();
    void connectSlots();
    void message( QString text );
    void logError( Errors error , QString fileName, int line );
    QString getHashString( QCryptographicHash::Algorithm algorithm
                           , QString inputString );

private slots:
    void savePassword();

private:
    Ui::ChangePasswordForm *ui;
    QSharedPointer<UserModel> _model;
    QString _userId;
    QMap<Errors, QString> _errors;
};

#endif // CHANGEPASSWORDFORM_H
