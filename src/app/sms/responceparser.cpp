#include "responceparser.h"
#include <QRegularExpression>
#include <QDebug>

ResponseParser::ResponseParser()
{
    initStatuses();
}


QString ResponseParser::getStatus( QString response )
{
    QRegularExpression re("^.*(\\d){4}-(\\d){2}-(\\d){2}.*$");
    QRegularExpressionMatch match = re.match( response );

    if ( response.contains( re, &match ) ) {
       return _statuses[ Status::ACCEPTED ];
    }
    else if ( response.contains( "DELIVRD", Qt::CaseInsensitive ) ) {
        return _statuses[ Status::DELIVRD ];
    }

    return _statuses[ Status::NOT_DELIVRD ];
}


QString ResponseParser::getMessageId( QString response )
{
    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match( response );

    if ( match.hasMatch() ) {
        return match.captured( 0 );
    }

    return "0";
}


void ResponseParser::initStatuses()
{
    _statuses[ Status::DELIVRD ] =
        "Доставлено";
    _statuses[ Status::ACCEPTED ] =
        "Доставляється";
    _statuses[ Status::NOT_DELIVRD ] =
        "Помилка";
}
