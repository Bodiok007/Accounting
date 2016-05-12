#ifndef LOGINFORMERROR_H
#define LOGINFORMERROR_H

enum class LoginFormError
{
    EMPTY_LOGIN_OR_PASSWORD,
    ERROR_QUERY,
    USER_NOT_FOUND,
    ERROR_SAVE_SETTING
};

#endif // LOGINFORMERROR_H